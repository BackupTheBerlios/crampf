#include <string>
#include "../options.hh"
#include "exit.hh"
#include <stdio.h>
#include "../iosubsys/output.hh"

void
Exit::doit( const std::string &s )
{
      throw std::string("exit");
}

void
Exit::help( const std::string &s ) const
{
  output->printf("format: exit\n");
  output->printf("description: Simmilar to quit. Exits the userinterface and\n");
  output->printf("returns but the current song is still played in background\n");
  output->printf("until it finishes.\n");
  output->printf("see also: quit\n");
}

void
Exit::description() const
{
      output->printf("exit, but play last song in background\n");
}
