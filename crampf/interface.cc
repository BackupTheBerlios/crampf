/*
 * Standard textmode interface
 */

#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include "interface.hh"
#include "config.hh"
#include "player.hh"

Interface::Interface( void )
{
  userexit = false;
  printf("WELCOME TO THE CRAMPF!\n");
  struct termios t;
  tcgetattr(1,&terminal_settings);
  t = terminal_settings;
  t.c_lflag&=~(ICANON|ECHO);
  tcsetattr(1,TCSANOW,&t);
  mainloop();
}

Interface::~Interface()
{
  tcsetattr(1,TCSANOW,&terminal_settings);
  printf("Thank you for using crampf!\n");
}

Interface::mainloop()
{
  char c;
  while (!userexit) {
    showstatus();
    c = fgetc(stdin); 
    if (opts->keys[c]!=NULL)
      (this->*(opts->keys[c]))();
  } 
}

Interface::showstatus()
{
  printf("[%d/%d] - %s\n",plist->pos(),plist->size(),
      (*(*plist)).title().c_str());
}

void
Interface::next( void )
{
  ++(*plist);
}

void
Interface::prev( void )
{
  --(*plist);
}

void
Interface::info( void )
{
  printf("not implemented yet\n");
}

void
Interface::pause( void )
{
  player_pause();
}

void
Interface::cont( void )
{
  player_continue();
}

void
Interface::list( void )
{
  printf("not implemented yet\n");
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
Interface::vol0( void )
{
  printf("not implemented yet\n");
}

void
Interface::vol1( void )
{
  printf("not implemented yet\n");
}

void
Interface::vol2( void )
{
  printf("not implemented yet\n");
}

void
Interface::vol3( void )
{
  printf("not implemented yet\n");
}

void
Interface::vol4( void )
{
  printf("not implemented yet\n");
}

void
Interface::vol5( void )
{
  printf("not implemented yet\n");
}

void
Interface::vol6( void )
{
  printf("not implemented yet\n");
}

void
Interface::vol7( void )
{
  printf("not implemented yet\n");
}

void
Interface::vol8( void )
{
  printf("not implemented yet\n");
}

void
Interface::vol9( void )
{
  printf("not implemented yet\n");
}

void
Interface::vol_up( void )
{
  printf("not implemented yet\n");
}

void
Interface::vol_down( void )
{
  printf("not implemented yet\n");
}
