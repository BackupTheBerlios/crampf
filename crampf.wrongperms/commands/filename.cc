#include <string>
#include "filename.hh"
#include "../playlist.hh"
#include "../track.hh"
#include <stdio.h>

extern Playlist* plist;

void
Filename::doit( string s )
{
  printf("filename: \"%s\"\n",(*(*plist)).filename().c_str());
}

void
Filename::help( string s )
{
  printf("format: filename\n");
  printf("description: shows full filename (with path) of current\n");
  printf("track.\n");
}

void
Filename::description()
{
  printf("display full filename with path\n");
}

