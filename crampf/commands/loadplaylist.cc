#include "../version_info.hh"
#include <string>
#include "../playlist.hh"
#include <stdio.h>
#include "loadplaylist.hh"

extern Playlist* plist;

void
LoadPlaylist::doit( string s )
{
  plist->addPlaylist(s);
}

void
LoadPlaylist::help( string s )
{
  printf("format: loadplaylist <filename>\n");
  printf("description: adds contents of playlist <filename> to the\n");
  printf("current playlist.\n");
  printf("see also: write\n");
}

void 
LoadPlaylist::description()
{
  printf("adds a playlistfile to the current playlist\n");
}
