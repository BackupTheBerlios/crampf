#include "../command.hh"
#include <string>
#include "../playlist.hh"
#include "loadnfilter.hh"

extern Playlist* plist;

void
LoadNFilter::doit( const string &s )
{
  plist->loadNegativeFilter( s );
}

void
LoadNFilter::help( const string &s ) const
{
  printf("format: loadnfilter <filterfile>\n");
  printf("description: does a nfilter command with each line of the\n");
  printf("filter file.\n");
  printf("see also: nfilter, pfilter, loadpfilter\n");
}

void 
LoadNFilter::description() const
{
  printf("loads negative filters from file\n");
}
