/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "set.hh"

void
Set::doit( const std::string &s )
{
  if (s=="list" || s=="all" || s=="show") {
    printf("---Options---\n");
    return;
    printf("not yet implemented :-(\n");
  }
}

void
Set::help( const std::string &s ) const
{
  printf("format: set <optionname>\n");
  printf("    or: set <optionname>=<value>\n");
  printf("    or: set <optionname> <value>\n");
  printf("    or: set all\n");
  printf("    or: set list\n");
  printf("    or: set show\n");
  printf("description: prints setting of option <optionname>,\n");
  printf("sets option <optionname> to value <value> or lists out\n");
  printf("all current settings\n");
}


void 
Set::description() const
{
  printf("change/view runtime options\n");
}
