#include "../command.hh"
#include <string>
#include "generatetitles.hh"
#include "../options.hh"
#include "../iosubsys/output.hh"

void
GenerateTitles::doit( const std::string &s )
{
  if (s.empty())
    output->printf("generatetitles: %s\n",(opts->generateTitles)?"Yes":"No");
  else switch (s[0]) {
    case 'y':
    case 'Y':
    case '1':
      opts->generateTitles=true;
      break;
    case 'n':
    case 'N':
    case '0':
      opts->generateTitles=false;
      break;
    default:
      output->printf("generatetitles: bad option\n");
  }
}

void
GenerateTitles::help( const std::string &s ) const
{
  output->printf("format: generatetitles [<value>]\n");
  output->printf("description: When turned on strips off search path from track\n");
  output->printf("titles during playlist generation.\n");
  output->printf("see also: status, filename\n");
}

void
GenerateTitles::description() const
{
  output->printf("strip titles\n");
}
