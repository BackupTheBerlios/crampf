#include "../playlist.hh"
#include "../player.hh"
#include "kill.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>

extern Playlist* plist;

void
Kill::doit( string s )
{
  if (s.empty()) {
    plist->erase(&(*plist)[plist->pos()]);
    player_play();
  } else {
    int d = atoi(s.c_str());
    if (d>0 && d<plist->size()) 
      plist->erase(&(*plist)[--d]);
  }
}

void
Kill::help( string s )
{
  printf("format: kill [<tracknumber>]\n");
  printf("description: removes current track or track <tracknumber>\n");
}

void
Kill::description()
{
  printf("removes tracks\n");
}