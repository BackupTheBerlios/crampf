#include "../playlist.hh"
#include "kill.hh"
#include "../player/player-interface.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>

extern Playlist* plist;
extern PlayerInterface *player;

void
Kill::doit( const std::string &s )
{
  if (s.empty()) {
    plist->erase( plist->Iterator() );
    player->play( (**plist).filename() );
  } else {
    int d = atoi(s.c_str());
    if (d>0 && d<(signed)plist->size()) 
      plist->erase( plist->Iterator( --d ) );
  }
}

void
Kill::help( const std::string &s ) const
{
  printf("format: kill [<tracknumber>]\n");
  printf("description: removes current track or track <tracknumber>\n");
}

void
Kill::description() const
{
  printf("removes tracks\n");
}
