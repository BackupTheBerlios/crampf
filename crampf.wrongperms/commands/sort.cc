#include "../playlist.hh"
#include "sort.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algo.h>
#include "../iosubsys/output.hh"

void
Sort::doit( const std::string &s )
{
      Track t( *(*plist) );
      sort( plist->begin(), plist->end() );
      plist->jump( 0 );
      while( t != *(*plist) )
	  (*plist)++;
}

void
Sort::help( const std::string &s ) const
{
  output->printf("format: sort\n");
  output->printf("description: sorts the playlist alphabetically\n");
  output->printf("see also: shuffle\n");
}

void
Sort::description() const
{
  output->printf("sorts playlist\n");
}
