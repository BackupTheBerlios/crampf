#include "../playlist.hh"
#include "../player.hh"
#include "sort.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <algo.h>

extern Playlist* plist;

void
Sort::doit( string s )
{
  sort( plist->begin(), plist->end() );
}

void
Sort::help( string s )
{
  printf("format: sort\n");
  printf("description: sorts the playlist alphabetically\n");
  printf("see also: shuffle\n");
}

void
Sort::description()
{
  printf("sorts playlist\n");
}
