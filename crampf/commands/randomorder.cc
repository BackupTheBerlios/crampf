#include "randomorder.hh"
#include <string>
#include <stdio.h>
#include "../options.hh"

extern struct options* opts;

void
RandomOrder::doit( const std::string &s )
{
  if (s.empty()) {
    printf("randomorder: %s\n",(opts->randomOrder)?"yes":"no");
    return;
  } else {
    switch (s[0]) {
      case 'y':
      case 'Y':
      case '1':
        opts->randomOrder = true;
        break;
      case 'n':
      case 'N':
      case '0':
        opts->randomOrder = false;
        break;
      default:
        throw std::string("randomorder: bad parameter");
    }
  }
}

void
RandomOrder::help( const std::string &s ) const
{
  printf("format: randomorder [<yes|no>]\n");
  printf("description: if activated playlist is shuffled at startup.\n");
  printf("Only useful in startup (config) file\n");
}

void RandomOrder::description() const
{
  printf("shuffle playlist at startup.\n");
}
          
