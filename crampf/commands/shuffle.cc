/*
 * scramble the playlist
 */

#include "../version_info.hh"
#include <string>
#include "../playlist.hh"
#include "shuffle.hh"

extern Playlist* plist;

  void
Shuffle::doit( string s )
{
  plist->shuffle();
}

void
Shuffle::help( string s )
{
  printf("shuffle\n");
  printf("scrambles the playlist\n");
}
