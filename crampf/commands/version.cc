#include "../version_info.hh"
#include "../command.hh"
#include "version.hh"
#include <string>
#include <stdio.h>

void
Version::doit( string s )
{
  printf("crampf %s %s\n",RELEASENAME,VERSION);
  printf("please send bugreports to logic@wg.netz\n");
}

void
Version::help( string s ) 
{
  printf("format: version\n");
  printf("description: prints out version information\n");
}
