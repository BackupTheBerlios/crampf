#include <string>
#include "../options.hh"
#include "exit.hh"
#include <stdio.h>

extern struct options* opts;

void
Exit::doit( const std::string &s )
{
      throw std::string("exit");
}

void
Exit::help( const std::string &s ) const
{
  printf("format: exit\n");
  printf("description: Simmilar to quit. Exits the userinterface and\n");
  printf("returns but the current song is still played in background\n");
  printf("until it finishes.\n");
  printf("see also: quit\n");
}

void
Exit::description() const
{
      printf("exit, but play last song in background\n");
}
