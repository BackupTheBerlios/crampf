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
#include "help.hh"

extern Playlist* plist;

Help::Help( CommandMap* c )
{
  cmap = c;
}

void
Help::doit( string s )
{
  cmap->help(s);
}

void
Help::help( string s )
{
  printf("help [command] -- displays short help (on command)\n");
}

