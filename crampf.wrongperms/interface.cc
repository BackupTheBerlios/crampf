/*
 * Standard textmode interface
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <string>
#include <map>
#include "interface.hh"
#include "config.hh"

Interface::Interface( void )
{
  printf("WELCOME TO THE CRAMPF!\n");
  struct termios t;
  if (tcgetattr(1,&terminal_settings)==-1) {
    perror("tcgetattr");
  }
  t = terminal_settings;
  t.c_lflag&=~(ICANON|ECHO);
  if (tcsetattr(1,TCSANOW,&t)==-1) {
    perror("tcsetattr");
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
  showstatus();
  try {
    char c;
    while (1) {
      c = fgetc(stdin); 
      if (opts->keys[c]!=NULL)
        (this->*(opts->keys[c]))();
    } 
  } catch (string s) {
    printf("%s\n",(const char*)s.c_str());
  }
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
  throw string("krampf: quit");
}

void 
Interface::info( void )
{
  printf("info\n");
  printf("not yet implemented\n");
}

void
Interface::list( void )
{
  printf("list\n");
  printf("not yet implemented\n");
}

void
Interface::next( void )
{
  ++(*plist);
  showstatus();
}

void
Interface::prev( void )
{
  --(*plist);
  showstatus();
}

void
Interface::jump( void )
{
  printf("jump\n");
  printf("not yet implemented\n");
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
  printf("vol_up\n");
  printf("not yet implemented\n");
}

void
Interface::vol_dn( void )
{
  printf("vol_dn\n");
  printf("not yet implemented\n");
}

void
Interface::pause( void )
{
  printf("pause\n");
  printf("not yet implemented\n");
}

void
Interface::cont( void )
{
  printf("cont\n");
  printf("not yet implemented\n");
}

Interface::changevol(int vol)
{
  char cmd[] = "aumix -s    ";
  if (vol<0 || vol>100)
    return -1;
  cmd[9]=48+vol%1000/100;
  cmd[10]=48+vol%100/10;
  cmd[11]=48+vol%10;
  if (system(cmd)==-1)
    perror("aumix");
}

Interface::showstatus()
{
  printf("[%d/%d] - %s\n",plist->pos()+1,plist->size(),
      (*(*plist)).title().c_str());
}
