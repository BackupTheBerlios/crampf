#include "../playlist.hh"
#include "../player.hh"
#include "sort.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algo.h>

extern Playlist* plist;

void
Sort::doit( const string &s )
{
      Track t( *(*plist) );
      sort( plist->begin(), plist->end() );
      plist->jump( 0 );
      while( t != *(*plist) )
	  (*plist)++;
}

void
Sort::help( const string &s ) const
{
  printf("format: sort\n");
  printf("description: sorts the playlist alphabetically\n");
  printf("see also: shuffle\n");
}

void
Sort::description() const
{
  printf("sorts playlist\n");
}
