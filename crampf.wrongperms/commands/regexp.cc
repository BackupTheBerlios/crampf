#include <string>
#include "../options.hh"
#include "regexp.hh"
#include <stdio.h>
#include "../iosubsys/output.hh"

void
RegExp::doit( const std::string &s )
{
      if (s.empty()) {
	  output->printf("regexp: ");
	  switch (opts->regexp) {
	      case 0: output->printf("disabled\n");
		      break;
	      case 1: output->printf("POSIX Basic Regular Expressions\n");
		      break;
	      case 2: output->printf("POSIX Extended Regular Expressions\n");
		      break;
	  }
      } else {
	  switch (s[0]) {
	      case 'o':			  /* `o'ff */
	      case 'O':
	      case 'd':			  /* `d'isable */
	      case 'D':
	      case 'n':			  /* `n'one */
	      case 'N': opts->regexp = 0;
			break;
	      case 'b':			  /* `b'asic regexps */
	      case 'B': opts->regexp = 1;
			break;
	      case 'e':			  /* `e'xtended regexps */
	      case 'E':
	      case 'x':			  /* e`x'tended regexps */
	      case 'X':	opts->regexp = 2;
			break;
	      default: throw std::string("regexp: unknown option");
	  }
      }
}

void
RegExp::help( const std::string &s ) const
{
  output->printf("format: regexp [<value>]\n");
  output->printf("description: Specifies what kind of regular expressions to use\n");
  output->printf("when searching through the playlist.\n");
  output->printf("Following types are available:\n");
  output->printf("off 	   - dont use regular expressions at all\n");
  output->printf("basic    - use POSIX regular expression syntax\n");
  output->printf("extended - use POSIX extended regular expression syntax\n");
  output->printf("When no <value> is given the current setting is printed.\n");
  output->printf("see also: search, rsearch, case\n");
}

void
RegExp::description() const
{
      output->printf("specify regular expression syntax\n");
}
