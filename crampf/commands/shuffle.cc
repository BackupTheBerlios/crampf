/*
 * scramble the playlist
 */

#include <string>
#include "../playlist.hh"
#include "shuffle.hh"

extern Playlist* plist;

  void
Shuffle::doit( const string &s )
{
  plist->shuffle();
}

void
Shuffle::help( const string &s ) const
{
  printf("format: shuffle\n");
  printf("description: scrambles the playlist\n");
}

void 
Shuffle::description() const
{
  printf("scrambles the playlist\n");
}
