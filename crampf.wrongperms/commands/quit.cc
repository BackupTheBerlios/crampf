/*
 * Here are all commands defined
 */


#include "../version_info.hh"
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
}

