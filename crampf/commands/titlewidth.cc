#include "../command.hh"
#include "../config.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "titlewidth.hh"

extern struct options* opts;

void
TitleWidth::doit( string s )
{
  if (s.empty()) {
    printf("titlewidth: %d\n",opts->titlewidth);
  } else {
    opts->titlewidth=atoi(s.c_str());
  }
}

void
TitleWidth::help( string s )
{
  printf("format: titlewidth <width>\n");
  printf("description: gets/sets linewidth of status command\n");
}

void
TitleWidth::description()
{
  printf("gets/sets linewidth of status command\n");
}
