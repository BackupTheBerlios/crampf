#include <string>
#include "../playlist.hh"
#include "pfilter.hh"
#include <stdio.h>
#include "../iosubsys/output.hh"

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
  output->printf("format: pfilter <word>\n");
  output->printf("description: filters all tracks out of the playlist which\n");
  output->printf("contain the word <word> in their full filename.\n");
  output->printf("see also: loadpfilter, nfilter\n");
}

void 
PFilter::description() const
{
  output->printf("filters current playlist\n");
}
