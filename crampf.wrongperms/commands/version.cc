#include "../command.hh"
#include "../config.h"
#include "version.hh"
#include <string>
#include <stdio.h>

void
Version::doit( const std::string &s )
{
  printf("crampf %s (C) 1999 by logic@tzi.org under GPL2\n",VERSION);
  printf("please send bugreports to logic@tzi.org\n");
}

void
Version::help( const std::string &s ) const
{
  printf("format: version\n");
  printf("description: prints out version information\n");
}

void 
Version::description() const
{
  printf("prints out version information\n");
}
