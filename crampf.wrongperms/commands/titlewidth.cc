#include "../command.hh"
#include "../options.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "titlewidth.hh"

extern struct options* opts;

void
TitleWidth::doit( const std::string &s )
{
  if (s.empty()) {
    printf("titlewidth: %d\n",opts->titlewidth);
  } else {
    opts->titlewidth=atoi(s.c_str());
  }
}

void
TitleWidth::help( const std::string &s ) const
{
  printf("format: titlewidth <width>\n");
  printf("description: gets/sets linewidth of status command\n");
  printf("see also: status\n");
}

void
TitleWidth::description() const
{
  printf("gets/sets linewidth of status command\n");
}
