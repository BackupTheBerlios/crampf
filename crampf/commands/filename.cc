#include <string>
#include "filename.hh"
#include "../playlist.hh"
#include "../track.hh"
#include <stdio.h>

extern Playlist* plist;

void
Filename::doit( const std::string &s )
{
  printf("filename: \"%s\"\n",(*(*plist)).filename().c_str());
}

void
Filename::help( const std::string &s ) const
{
  printf("format: filename\n");
  printf("description: shows full filename (with path) of current\n");
  printf("track.\n");
  printf("see also: status, info\n");
}

void
Filename::description() const
{
  printf("display full filename with path\n");
}

