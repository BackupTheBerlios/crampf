#include "../command.hh"
#include "../config.h"
#include "version.hh"
#include <string>
#include <stdio.h>

void
Version::doit( const string &s )
{
  printf("crampf %s\n",VERSION);
  printf("please send bugreports to logic@tzi.de\n");
}

void
Version::help( const string &s ) const
{
  printf("format: version\n");
  printf("description: prints out version information\n");
}

void 
Version::description() const
{
  printf("prints out version information\n");
}
