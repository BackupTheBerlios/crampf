/*
 * Adds a path or file to the playlist
 */

#include <string>
#include "addpath.hh"
#include "../playlist.hh"

extern Playlist* plist;

void
AddPath::doit( string s )
{
  plist->addPath(s);
}

void
AddPath::help( string s )
{
  printf("addPath <path>\n");
  printf("adds a path or file to current playlist\n");
}
