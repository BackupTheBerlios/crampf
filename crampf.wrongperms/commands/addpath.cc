/*
 * Adds a path or file to the playlist
 */

#include <string>
#include "addpath.hh"
#include "../playlist.hh"

extern Playlist* plist;

void
AddPath::doit( const string &s )
{
  string str(s);
  for (int i=str.size()-1; str[i]==' '; i--)
    str.erase(i);
  plist->addPath(str);
}

void
AddPath::help( const string &s ) const
{
  printf("format: addpath <path>\n");
  printf("description: adds a path or file to current playlist\n");
}

void 
AddPath::description() const
{
  printf("adds a path or file to current playlist\n");
}

