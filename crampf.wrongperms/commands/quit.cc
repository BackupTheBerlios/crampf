/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "quit.hh"

void
Quit::doit( string s )
{
  throw string("quit");
}

void
Quit::help( string s )
{
  printf("quit -- guess what it does :-)\n");
  printf("see also: exit\n");
}

void 
Quit::description()
{
  printf("guess what it does :-)\n");
}
