
#include <string>
#include "../playlist.hh"
#include <stdio.h>
#include <stdlib.h>
#include "write.hh"

extern Playlist* plist;

void
Write::doit( string s )
{
  if (s.empty()) {
    if (filename.empty()) {
      printf("no filename\n");
      commit = false;
    } else if (commit) {
      commit = false;
      printf("writing playlist to file `%s'\n",filename.c_str());
      plist->savePlaylist(filename);
    } else {
      printf("write playlist to file `%s'? (repeat to commit)\n",filename.c_str());
      commit = true;
    }
  } else {
    commit = false;
    filename = s;
    printf("writing playlist to file `%s'\n",filename.c_str());
    plist->savePlaylist(filename);
  }
}

void
Write::help( string s )
{
  printf("format: write [<filename>]\n");
  printf("description: write contents of playlist to file <filename>\n");
  printf("see also: loadplaylist\n");
}

void
Write::description()
{
  printf("write contents of playlist to file <filename>\n");
}
