#include <string>
#include "../playlist.hh"
#include <stdio.h>
#include "loadplaylist.hh"

extern Playlist* plist;

void
LoadPlaylist::doit( const string &s )
{
  plist->addPlaylist(s);
}

void
LoadPlaylist::help( const string &s ) const
{
  printf("format: loadplaylist <filename>\n");
  printf("description: adds contents of playlist <filename> to the\n");
  printf("current playlist.\n");
  printf("see also: write\n");
}

void 
LoadPlaylist::description() const
{
  printf("adds a playlistfile to the current playlist\n");
}
