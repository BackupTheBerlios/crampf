/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "quit.hh"
#include "../iosubsys/output.hh"

void
Quit::doit( const std::string &s )
{
  throw std::string("quit");
}

void
Quit::help( const std::string &s ) const
{
  output->printf("quit -- guess what it does :-)\n");
  output->printf("see also: exit\n");
}

void 
Quit::description() const
{
  output->printf("guess what it does :-)\n");
}
