#include "../command.hh"
#include <string>
#include "../playlist.hh"
#include "loadpfilter.hh"
#include "../iosubsys/output.hh"

void
LoadPFilter::doit( const std::string &s )
{
  plist->loadPositiveFilter( s );
}

void
LoadPFilter::help( const std::string &s ) const
{
  output->printf("format: loadpfilter <filterfile>\n");
  output->printf("description: does a pfilter command with each line of the\n");
  output->printf("filter file.\n");
  output->printf("see also: pfilter, nfilter, loadnfilter\n");
}

void 
LoadPFilter::description() const
{
  output->printf("loads positive filters from file\n");
}
