/*
 * Standard textmode interface
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string>
#include <map>
#include "interface.hh"
#include "player.hh"
#include "config.hh"

Interface::Interface( void )
{
  printf("WELCOME TO THE CRAMPF!\n");
  detectSoundCard();
  volume = getVolume();
  struct termios t;
  if (tcgetattr(1,&terminal_settings)==-1) {
    perror("tcgetattr");
  }
  t = terminal_settings;
  t.c_lflag&=~(ICANON|ECHO);
  if (tcsetattr(1,TCSANOW,&t)==-1) {
    perror("tcsetattr");
  }
  if (fcntl(1,F_SETFL, O_NONBLOCK)==-1) {
    perror("fcntl");
  }
  mainloop();
}

Interface::~Interface()
{
  if (tcsetattr(1,TCSANOW,&terminal_settings)==-1) {
    perror("tcsettatr");
  }
  printf("Thank you for using crampf!\n");
}

Interface::mainloop()
{
  player_init();
  player_play();
  try {
    char c;
    while (1) {
      if (player_restarted()) {
        showstatus();
      }
      usleep(100);
      c = fgetc(stdin); 
      if (opts->keys[c]!=NULL) 
        (this->*(opts->keys[c]))();
      c = '\0'; 
    } 
  } catch (string s) {
    printf("%s\n",(const char*)s.c_str());
  }
  player_stop();
}

void
Interface::help( void )
{
  int col=0;
  printf("\ncrampf developers v0.0 -- help\n");
  printf("==============================\n");
  for (map<string, string>::iterator it = opts->keytable.begin();
      it != opts->keytable.end(); it++) {
    printf("%s\t[",it->first.c_str());
    for (int i=0; i<it->second.size(); i++) {
      printf("%c",it->second[i]);
      if (i+1<it->second.size())
        printf(",");
    }
    printf("]");
    if ((++col)%2==0) {
      printf("\n");
    } else {
      printf("\t");
    }
  }
  printf("\n\n");
}

void
Interface::quit( void )
{
  throw string("");
}

void 
Interface::info( void )
{
  int pid;
  pid = fork();
  if (pid==0) {
    execlp("mp3info","mp3info",(*(*plist)).filename().c_str(),"-F 2",NULL);
    perror("execlp(mp3info)");
    exit(1);
  }
}

void
Interface::list( void )
{
  printf("list\n");
  printf("not yet implemented\n");
}

void
Interface::file( void )
{
  printf("filename: ``%s''\n",(*(*plist)).filename().c_str());
}

void
Interface::next( void )
{
  ++(*plist);
  player_play();
}

void
Interface::prev( void )
{
  --(*plist);
  player_play();
}

void
Interface::jump( void )
{
  printf("jump\n");
  printf("not yet implemented\n");
}

void
Interface::pause( void )
{
  printf("pause\n");
  player_pause();
}

void
Interface::cont( void )
{
  printf("cont\n");
  player_continue();
}

void
Interface::vol0( void )
{
  changevol(0);
}

void
Interface::vol1( void )
{
  changevol(10);
}

void
Interface::vol2( void )
{
  changevol(20);
}

void
Interface::vol3( void )
{
  changevol(30);
}

void
Interface::vol4( void )
{
  changevol(40);
}

void
Interface::vol5( void )
{
  changevol(50);
}

void
Interface::vol6( void )
{
  changevol(60);
}

void
Interface::vol7( void )
{
  changevol(70);
}

void
Interface::vol8( void )
{
  changevol(80);
}

void
Interface::vol9( void )
{
  changevol(90);
}

void
Interface::vol_up( void )
{
  if (volume-5>0) {
    volume+=5;
    changevol(volume);
  }
}

void
Interface::vol_dn( void )
{
  if (volume+5<100) {
    volume-=5;
    changevol(volume);
  }
}

Interface::changevol(int vol)
{
  int pid;
  char arg[6];
  if (vol<0 || vol>100)
    return -1;
  volume = vol;
  arg[0]='-';
  arg[1]=opts->soundcard;
  arg[2]=48+vol%1000/100;
  arg[3]=48+vol%100/10;
  arg[4]=48+vol%10;
  arg[5]='\0';
  pid = fork();
  if (pid==0) {
    execlp("aumix","aumix",arg,NULL);
    perror("execlp(aumix)");
    exit(1);
  } 
  /* player will reap the child */
}
 
Interface::detectSoundCard()
{
  opts->soundcard='w'; /* default */
  FILE* fp = fopen("/dev/sndstat","r");
  if (fp==NULL) {
    perror("sndstat");
    return -1;
  }
#define LINEWIDTH 128
  char line[LINEWIDTH];
  string l;
  while (fgets(line,LINEWIDTH,fp)) {
    l=line;
    if (l.find("UltraSound")!=-1)
      opts->soundcard='s';
  }
  fclose(fp);
}

int
Interface::getVolume()
{
  FILE* fp = popen("aumix -q","r");
  char line[LINEWIDTH];
  char rs[5];
  char ls[5];
  int ri=40; /* default setting */
  int li=40;
  while (fgets(line,LINEWIDTH,fp)) {
    if (strncmp("synth",line,5)==0) {
      sscanf(line,"%*[a-z]%*[\t ]%[0-9]%*[, ]%[0-9]\n",ls,rs);
      ri=atoi(rs);
      li=atoi(ls);
    }
  }
  pclose(fp);
  return ((ri+li)/2);
}

Interface::showstatus()
{
  if (opts->titlewidth==0) {
  printf("\n[%d/%d] - %s\n",plist->pos()+1,plist->size(),
      (*(*plist)).title().c_str());
  } else {
#define MAXTITLEWIDTH 1024
    char title[MAXTITLEWIDTH];
    sprintf(title,"\n[%d/%d] - %s\n",plist->pos()+1,plist->size(),
      (*(*plist)).title().c_str());
    if (strlen(title)>opts->titlewidth) {
      int i;
      for (i=0; i<opts->titlewidth/3; i++)
        printf("%c",title[i]);
      printf("...");
      i=strlen(title)-i*2-1;
      for (;i<strlen(title);i++)
        printf("%c",title[i]);
    } else 
      printf("%s",title);
  }
}
