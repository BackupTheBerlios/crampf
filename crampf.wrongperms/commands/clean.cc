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
      int newpos = plist->pos();
      for( int i=0; i<plist->size(); i++ )
	  if( player->supportedFormat( (*plist)[i].filename() ) == 0.0 ){
	      if( i < plist->pos() )
		  newpos--;
	      stck.push( plist->Iterator( i ) );
	  }
      while (!stck.empty()) {
	  plist->erase(stck.top());
	  stck.pop();
      }
      plist->jump( newpos );
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
