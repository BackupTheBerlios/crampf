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
#include "next.hh"

extern Playlist* plist;

void
Next::doit( string s )
{
  ++(*plist);
  player_play();
}

void
Next::help( string s )
{
  printf("skips forward to next song\n");
}

