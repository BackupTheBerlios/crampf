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
#include "info.hh"

extern Playlist* plist;

void
Info::doit( string s )
{
  printf("not yet implemented\n");
}

void
Info::help( string s )
{
  printf("shows information on current title\n");
}

