
#include <string>
#include "../playlist.hh"
#include <stdio.h>
#include <stdlib.h>
#include "write.hh"
#include "../iosubsys/output.hh"

void
Write::doit( const std::string &s )
{
  if (s.empty()) {
    if (filename.empty()) {
      output->printf("no filename\n");
      commit = false;
    } else if (commit) {
      commit = false;
      output->printf("writing playlist to file `%s'\n",filename.c_str());
      plist->savePlaylist(filename);
    } else {
      output->printf("write playlist to file `%s'? (repeat to commit)\n",filename.c_str());
      commit = true;
    }
  } else {
    commit = false;
    filename = s;
    output->printf("writing playlist to file `%s'\n",filename.c_str());
    plist->savePlaylist(filename);
  }
}

void
Write::help( const std::string &s ) const
{
  output->printf("format: write [<filename>]\n");
  output->printf("description: write contents of playlist to file <filename>\n");
  output->printf("see also: loadplaylist\n");
}

void
Write::description() const
{
  output->printf("write contents of playlist to file <filename>\n");
}
