#include "../version_info.hh"
#include "../command.hh"
#include "version.hh"
#include <string>
#include <stdio.h>

void
Version::doit( string s )
{
  printf("crampf %s %s\n",RELEASENAME,VERSION_INFO);
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
