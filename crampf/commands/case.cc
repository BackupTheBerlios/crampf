#include <string>
#include "../options.hh"
#include "case.hh"
#include <stdio.h>
#include "../iosubsys/output.hh"

void
Case::doit( const std::string &s )
{
      if (s.empty()) {
	  output->printf("case: %s\n",(opts->casesensivity)?"respect":"ignore");
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
  output->printf("format: case [<value>]\n");
  output->printf("description: Specifies wether to ignore case in searches or not\n");
  output->printf("If <value> is \"ignore\" casesensivity is disabled, if set to\n");
  output->printf("\"respect\" case matters in searches. Case insensivity is only\n");
  output->printf("provided in regexp searches. If no <value> is given the\n");
  output->printf("current setting is printed.\n");
  output->printf("see also: regexp, search, rsearch\n");
}

void
Case::description() const
{
      output->printf("toggle case sensivity on searches\n");
}
