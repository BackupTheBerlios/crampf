/*
 * scramble the playlist
 */

#include <string>
#include "../playlist.hh"
#include "shuffle.hh"
#include "../iosubsys/output.hh"

  void
Shuffle::doit( const std::string &s )
{
  plist->shuffle();
}

void
Shuffle::help( const std::string &s ) const
{
  output->printf("format: shuffle\n");
  output->printf("description: scrambles the playlist\n");
}

void 
Shuffle::description() const
{
  output->printf("scrambles the playlist\n");
}
