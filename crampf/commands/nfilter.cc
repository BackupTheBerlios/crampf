#include "../version_info.hh"
#include <string>
#include "../playlist.hh"
#include "nfilter.hh"
#include <stdio.h>

extern Playlist* plist;

void
NFilter::doit( string s )
{
  if (s.empty())
    throw string("filter: parameter missing!");
  plist->negativeFilter(s);
}

void
NFilter::help( string s )
{
  printf("format: nfilter <word>\n");
  printf("description: filters all tracks out of the playlist which\n");
  printf("contain the word <word> in their full filename.\n");
}

void 
NFilter::description()
{
  printf("filters current playlist\n");
}