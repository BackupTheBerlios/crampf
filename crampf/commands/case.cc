#include <string>
#include "../config.hh"
#include "case.hh"
#include <stdio.h>

extern struct options* opts;

void
Case::doit( const std::string &s )
{
      if (s.empty()) {
	  printf("case: %s\n",(opts->casesensivity)?"respect":"ignore");
      } else {
	  if (s[0]=='i' || s[0]=='I') { /* `i'gnore */
	      opts->casesensivity = false;
	  } else {
	      opts->casesensivity = true;
	  }
      }
}

void
Case::help( const std::string &s ) const
{
  printf("format: case [<value>]\n");
  printf("description: Specifies wether to ignore case in searches or not\n");
  printf("If <value> is \"ignore\" casesensivity is disabled, if set to\n");
  printf("\"respect\" case matters in searches. Case insensivity is only\n");
  printf("provided in regexp searches. If no <value> is given the\n");
  printf("current setting is printed.\n");
  printf("see also: regexp, search, rsearch\n");
}

void
Case::description() const
{
      printf("toggle case sensivity on searches\n");
}
