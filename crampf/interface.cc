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

Interface::showstatus()
{
  printf("[%d/%d] - %s\n",plist->pos(),plist->size(),
      (*(*plist)).title().c_str());
}
