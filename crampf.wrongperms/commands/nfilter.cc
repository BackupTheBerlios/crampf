#include <string>
#include "../playlist.hh"
#include "nfilter.hh"
#include <stdio.h>

extern Playlist* plist;

void
NFilter::doit( const std::string &s )
{
  if (s.empty())
    throw std::string("filter: parameter missing!");
  plist->negativeFilter(s);
}

void
NFilter::help( const std::string &s ) const
{
  printf("format: nfilter <word>\n");
  printf("description: filters all tracks out of the playlist which\n");
  printf("contain the word <word> in their full filename.\n");
  printf("see also: loadnfilter, pfilter\n");
}

void 
NFilter::description() const
{
  printf("filters current playlist\n");
}
