#include <string>
#include "../config.hh"
#include "regexp.hh"
#include <stdio.h>

extern struct options* opts;

void
RegExp::doit( const string &s )
{
      if (s.empty()) {
	  printf("regexp: ");
	  switch (opts->regexp) {
	      case 0: printf("disabled\n");
		      break;
	      case 1: printf("POSIX Basic Regular Expressions\n");
		      break;
	      case 2: printf("POSIX Extended Regular Expressions\n");
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
	      default: throw string("regexp: unknown option");
	  }
      }
}

void
RegExp::help( const string &s ) const
{
  printf("format: regexp [<value>]\n");
  printf("description: Specifies what kind of regular expressions to use\n");
  printf("when searching through the playlist.\n");
  printf("Following types are available:\n");
  printf("off 	   - dont use regular expressions at all\n");
  printf("basic    - use POSIX regular expression syntax\n");
  printf("extended - use POSIX extended regular expression syntax\n");
  printf("When no <value> is given the current setting is printed.\n");
  printf("see also: search, rsearch, case\n");
}

void
RegExp::description() const
{
      printf("specify regular expression syntax\n");
}
