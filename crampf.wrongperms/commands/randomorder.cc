#include "randomorder.hh"
#include <string>
#include <stdio.h>
#include "../options.hh"
#include "../iosubsys/output.hh"

void
RandomOrder::doit( const std::string &s )
{
  if (s.empty()) {
    output->printf("randomorder: %s\n",(opts->randomOrder)?"yes":"no");
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
  output->printf("format: randomorder [<yes|no>]\n");
  output->printf("description: if activated playlist is shuffled at startup.\n");
  output->printf("Only useful in startup (config) file\n");
}

void RandomOrder::description() const
{
  output->printf("shuffle playlist at startup.\n");
}
          
