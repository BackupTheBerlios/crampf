#include "../command.hh"
#include <string>
#include "../playlist.hh"
#include "loadnfilter.hh"
#include "../iosubsys/output.hh"

void
LoadNFilter::doit( const std::string &s )
{
  plist->loadNegativeFilter( s );
}

void
LoadNFilter::help( const std::string &s ) const
{
  output->printf("format: loadnfilter <filterfile>\n");
  output->printf("description: does a nfilter command with each line of the\n");
  output->printf("filter file.\n");
  output->printf("see also: nfilter, pfilter, loadpfilter\n");
}

void 
LoadNFilter::description() const
{
  output->printf("loads negative filters from file\n");
}
