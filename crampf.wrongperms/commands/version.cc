#include "../command.hh"
#include "../config.h"
#include "version.hh"
#include <string>
#include <stdio.h>

void
Version::doit( string s )
{
  printf("crampf %s\n",VERSION);
  printf("please send bugreports to logic@tzi.de\n");
}

void
Version::help( string s ) 
{
  printf("format: version\n");
  printf("description: prints out version information\n");
}

void 
Version::description()
{
  printf("prints out version information\n");
}
