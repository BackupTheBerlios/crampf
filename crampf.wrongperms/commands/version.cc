#include "../command.hh"
#include "../config.h"
#include "version.hh"
#include <string>
#include <stdio.h>
#include "../iosubsys/output.hh"

void
Version::doit( const std::string &s )
{
  output->printf("crampf %s (C) 1999 by logic@tzi.org under GPL2\n",VERSION);
  output->printf("please send bugreports to logic@tzi.org\n");
}

void
Version::help( const std::string &s ) const
{
  output->printf("format: version\n");
  output->printf("description: prints out version information\n");
}

void 
Version::description() const
{
  output->printf("prints out version information\n");
}
