#include <string>
#include "../playlist.hh"
#include "nfilter.hh"
#include <stdio.h>
#include "../iosubsys/output.hh"

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
  output->printf("format: nfilter <word>\n");
  output->printf("description: filters all tracks out of the playlist which\n");
  output->printf("contain the word <word> in their full filename.\n");
  output->printf("see also: loadnfilter, pfilter\n");
}

void 
NFilter::description() const
{
  output->printf("filters current playlist\n");
}
