#include <string>
#include "../playlist.hh"
#include <stdio.h>
#include "loadplaylist.hh"
#include "../iosubsys/output.hh"

void
LoadPlaylist::doit( const std::string &s )
{
  plist->addPlaylist(s);
}

void
LoadPlaylist::help( const std::string &s ) const
{
  output->printf("format: loadplaylist <filename>\n");
  output->printf("description: adds contents of playlist <filename> to the\n");
  output->printf("current playlist.\n");
  output->printf("see also: write\n");
}

void 
LoadPlaylist::description() const
{
  output->printf("adds a playlistfile to the current playlist\n");
}
