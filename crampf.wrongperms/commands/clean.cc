#include "clean.hh"
#include <stdio.h>
#include <string>
#include <stack>
#include "../playlist.hh"
#include "../player/player-interface.hh"
#include "../iosubsys/output.hh"

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
  output->printf("format: clean\n");
  output->printf("description: removes unsupported entries in playlist\n");
}

void
Clean::description() const
{
  output->printf("removes unsupported entries in playlist\n");
}
