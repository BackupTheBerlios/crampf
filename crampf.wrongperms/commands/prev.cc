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
#include "prev.hh"

extern Playlist* plist;

void
Prev::doit( string s )
{
  --(*plist);
  player_play();
}

void
Prev::help( string s )
{
  printf("skips backward to previous song\n");
}

