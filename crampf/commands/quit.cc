/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "quit.hh"

void
Quit::doit( const std::string &s )
{
  throw std::string("quit");
}

void
Quit::help( const std::string &s ) const
{
  printf("quit -- guess what it does :-)\n");
  printf("see also: exit\n");
}

void 
Quit::description() const
{
  printf("guess what it does :-)\n");
}
