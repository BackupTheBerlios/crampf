/*
 * Adds a path or file to the playlist
 */

#include <string>
#include "addpath.hh"
#include "../playlist.hh"
#include "../iosubsys/output.hh"

void
AddPath::doit( const std::string &s )
{
  std::string str(s);
  for (int i=str.size()-1; str[i]==' '; i--)
    str.erase(i);
  plist->addPath(str);
}

void
AddPath::help( const std::string &s ) const
{
  output->printf("format: addpath <path>\n");
  output->printf("description: adds a path or file to current playlist\n");
}

void 
AddPath::description() const
{
  output->printf("adds a path or file to current playlist\n");
}

