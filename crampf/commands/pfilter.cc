#include <string>
#include "../playlist.hh"
#include "pfilter.hh"
#include <stdio.h>

extern Playlist* plist;

void
PFilter::doit( const std::string &s )
{
  if (s.empty())
    throw std::string("filter: parameter missing!");
  plist->positiveFilter(s);
}

void
PFilter::help( const std::string &s ) const
{
  printf("format: pfilter <word>\n");
  printf("description: filters all tracks out of the playlist which\n");
  printf("contain the word <word> in their full filename.\n");
  printf("see also: loadpfilter, nfilter\n");
}

void 
PFilter::description() const
{
  printf("filters current playlist\n");
}
