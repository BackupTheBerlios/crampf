/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "set.hh"
#include "../iosubsys/output.hh"

void
Set::doit( const std::string &s )
{
  if (s=="list" || s=="all" || s=="show") {
    output->printf("---Options---\n");
    return;
    output->printf("not yet implemented :-(\n");
  }
}

void
Set::help( const std::string &s ) const
{
  output->printf("format: set <optionname>\n");
  output->printf("    or: set <optionname>=<value>\n");
  output->printf("    or: set <optionname> <value>\n");
  output->printf("    or: set all\n");
  output->printf("    or: set list\n");
  output->printf("    or: set show\n");
  output->printf("description: prints setting of option <optionname>,\n");
  output->printf("sets option <optionname> to value <value> or lists out\n");
  output->printf("all current settings\n");
}


void 
Set::description() const
{
  output->printf("change/view runtime options\n");
}
