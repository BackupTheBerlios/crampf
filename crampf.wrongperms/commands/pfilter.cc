#include "../version_info.hh"
#include <string>
#include "../playlist.hh"
#include "pfilter.hh"
#include <stdio.h>

extern Playlist* plist;

void
PFilter::doit( string s )
{
  plist->positiveFilter(s);
}

void
PFilter::help( string s )
{
  printf("format: pfilter <word>\n");
  printf("description: filters all tracks out of the playlist which\n");
  printf("contain the word <word> in their full filename.\n");
}

void 
PFilter::description()
{
  printf("filters current playlist\n");
}
