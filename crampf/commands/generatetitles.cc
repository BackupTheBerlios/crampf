#include "../command.hh"
#include <string>
#include "generatetitles.hh"
#include "../config.hh"

extern struct options* opts;

void
GenerateTitles::doit( const std::string &s )
{
  if (s.empty())
    printf("generatetitles: %s\n",(opts->generateTitles)?"Yes":"No");
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
      printf("generatetitles: bad option\n");
  }
}

void
GenerateTitles::help( const std::string &s ) const
{
  printf("format: generatetitles [<value>]\n");
  printf("description: When turned on strips off search path from track\n");
  printf("titles during playlist generation.\n");
  printf("see also: status, filename\n");
}

void
GenerateTitles::description() const
{
  printf("strip titles\n");
}
