/*
 * Standard textmode interface
 */

#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include "interface.hh"
#include "config.hh"

Interface::Interface( void )
{
  userexit = false;
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
  char c;
  while (!userexit) {
    showstatus();
    c = fgetc(stdin); 
    printf("%x, %s, %d\n",opts->keys[c],opts->keys[c],opts->keys[c]);
    if (opts->keys[c]!=NULL)
      (this->*(opts->keys[c]))();
  } 
}

void
Interface::help( void )
{
  printf("crampf v0.0 -- help\n");
}

void
Interface::quit( void )
{
  userexit = true;
}

void 
Interface::info( void )
{
  printf("info\n");
}

void
Interface::list( void )
{
  printf("list\n");
}

void
Interface::next( void )
{
  printf("next\n");
}

void
Interface::prev( void )
{
  printf("prev\n");
}

void
Interface::jump( void )
{
  printf("jump\n");
}

void
Interface::vol0( void )
{
  printf("vol0\n");
}

void
Interface::vol1( void )
{
  printf("vol1\n");
}

void
Interface::vol2( void )
{
  printf("vol2\n");
}

void
Interface::vol3( void )
{
  printf("vol3\n");
}

void
Interface::vol4( void )
{
  printf("vol4\n");
}

void
Interface::vol5( void )
{
  printf("vol5\n");
}

void
Interface::vol6( void )
{
  printf("vol6\n");
}

void
Interface::vol7( void )
{
  printf("vol7\n");
}

void
Interface::vol8( void )
{
  printf("vol8\n");
}

void
Interface::vol9( void )
{
  printf("vol9\n");
}

void
Interface::vol_up( void )
{
  printf("vol_up\n");
}

void
Interface::vol_down( void )
{
  printf("vol_down\n");
}

Interface::showstatus()
{
  printf("[%d/%d] - %s\n",plist->pos(),plist->size(),
      (*(*plist)).title().c_str());
}
