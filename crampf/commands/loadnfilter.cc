#include "../version_info.hh"
#include "../command.hh"
#include <string>
#include "../playlist.hh"
#include "loadnfilter.hh"

extern Playlist* plist;

void
LoadNFilter::doit( string s )
{
  printf("not yet implemented\n");
  /* es gibt noch keine allgemeine Funktion zum laden eines
     Filterfiles (die einzige versteckt sich im Config Objekt */
}

void
LoadNFilter::help( string s )
{
  printf("format: loadnfilter <filterfile>\n");
  printf("description: does a nfilter command with each line of the\n");
  printf("filter file.\n");
  printf("see also: nfilter, pfilter, loadpfilter\n");
}

void 
LoadNFilter::description()
{
  printf("loads negative filters from file\n");
}
