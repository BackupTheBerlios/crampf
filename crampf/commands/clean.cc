#include "clean.hh"
#include <stdio.h>
#include <string>
#include <stack>
#include "../playlist.hh"
#include "../player/player-interface.hh"

extern Playlist* plist;
extern PlayerInterface *player;

void
Clean::doit( const std::string &s )
{
  std::stack<Playlist::iterator> stck;
  for (Playlist::iterator it = plist->begin();
      it != plist->end(); it++) 
      if( player->supportedFormat( it->filename() ) == 0.0 )
	  stck.push( it );
  while (!stck.empty()) {
    plist->erase(stck.top());
    stck.pop();
  }
}

void
Clean::help( const std::string &s ) const
{
  printf("format: clean\n");
  printf("description: removes unsupported entries in playlist\n");
}

void
Clean::description() const
{
  printf("removes unsupported entries in playlist\n");
}
