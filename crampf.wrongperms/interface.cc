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
extern "C" {
#include <readline/readline.h>
#include <readline/history.h>
}
#include <string>
#include <map>
#include "interface.hh"
#include "player.hh"
#include "config.hh"

Interface::Interface( void )
{
  printf("WELCOME TO THE CRAMPF!\n");
  detectSoundCard();
  opts->volume = getVolume();
  /* save terminal settings */
  if (tcgetattr(1,&terminal_settings)==-1) {
    perror("tcgetattr");
  }
  singlekeyTerm();
  mainloop();
}
  
Interface::~Interface()
{
  restoreTerm();
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
        opts->cmdmap["status"];
      }
      usleep(100);
      c = fgetc(stdin); 
      if (c!=EOF) {
        if (c==':') {
          rli();
        } else {
          try {
            opts->cmdmap[c];
          } catch (string error) {
            if (error=="quit")
              throw error;
            printf("error: `%s'\n",error.c_str());
          } 
        } 
      } 
    }
  } catch (string error) {
    if (error!="quit")
      printf("error: `%s'\n",error.c_str());
  }
  player_stop();
}

void
Interface::singlekeyTerm() 
{
  struct termios t;
  t = terminal_settings;
  t.c_lflag&=~(ICANON|ECHO);
  if (tcsetattr(1,TCSANOW,&t)==-1) {
    perror("tcsetattr");
  }
  if (fcntl(1,F_SETFL, O_NONBLOCK)==-1) {
    perror("fcntl");
  }
}

void
Interface::restoreTerm()
{
  if (tcsetattr(1,TCSANOW,&terminal_settings)==-1) {
    perror("tcsettatr");
  }
}

/*
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
*/

void
Interface::rli( void )
{
  restoreTerm();
  char* cmd = readline(":");
  try {
    opts->cmdmap[cmd];
  } catch (string error) {
    if (error=="quit")
      throw error;
    printf("error: `%s'\n",error.c_str());
  }
  free(cmd);
  singlekeyTerm();
}

/*
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
  // player will reap the child 
}
*/

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

