#include "../command.hh"
#include <string>
#include "../playlist.hh"
#include "loadpfilter.hh"

extern Playlist* plist;

void
LoadPFilter::doit( const string &s )
{
  plist->loadPositiveFilter( s );
}

void
LoadPFilter::help( const string &s ) const
{
  printf("format: loadpfilter <filterfile>\n");
  printf("description: does a pfilter command with each line of the\n");
  printf("filter file.\n");
  printf("see also: pfilter, nfilter, loadnfilter\n");
}

void 
LoadPFilter::description() const
{
  printf("loads positive filters from file\n");
}
