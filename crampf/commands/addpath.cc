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
  for (int i=s.size()-1; s[i]==' '; i--)
    s.erase(i);
  plist->addPath(s);
}

void
AddPath::help( string s )
{
  printf("format: addpath <path>\n");
  printf("description: adds a path or file to current playlist\n");
}

void 
AddPath::description()
{
  printf("adds a path or file to current playlist\n");
}

