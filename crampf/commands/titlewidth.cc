#include "../command.hh"
#include "../options.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "titlewidth.hh"
#include "../iosubsys/output.hh"

void
TitleWidth::doit( const std::string &s )
{
  if (s.empty()) {
    output->printf("titlewidth: %d\n",opts->titlewidth);
  } else {
    opts->titlewidth=atoi(s.c_str());
  }
}

void
TitleWidth::help( const std::string &s ) const
{
  output->printf("format: titlewidth <width>\n");
  output->printf("description: gets/sets linewidth of status command\n");
  output->printf("see also: status\n");
}

void
TitleWidth::description() const
{
  output->printf("gets/sets linewidth of status command\n");
}
