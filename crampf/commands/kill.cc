#include "../playlist.hh"
#include "../player.hh"
#include "kill.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>

extern Playlist* plist;
extern PlayerInterface *player;

void
Kill::doit( const string &s )
{
  if (s.empty()) {
    plist->erase(&(*plist)[plist->pos()]);
    player->play();
  } else {
    int d = atoi(s.c_str());
    if (d>0 && d<(signed)plist->size()) 
      plist->erase(&(*plist)[--d]);
  }
}

void
Kill::help( const string &s ) const
{
  printf("format: kill [<tracknumber>]\n");
  printf("description: removes current track or track <tracknumber>\n");
}

void
Kill::description() const
{
  printf("removes tracks\n");
}
