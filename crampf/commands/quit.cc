/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "../player.hh"
#include "../playlist.hh"
#include "quit.hh"

extern Playlist* plist;

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

