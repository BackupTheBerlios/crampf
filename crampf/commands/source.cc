#include "../command.hh"
#include "../commandmap.hh"
#include <string>
#include "source.hh"
#include "../file.hh"

Source::Source( CommandMap* c )
{
  cmap = c;
}

void
Source::doit( string s )
{
  try {
    File f(s);
    while (1)
      (*cmap)[++f];
  } catch (string error) {
    if (error!="end of file")
      printf("source: %s\n",error.c_str());
  }
}

void
Source::help( string s )
{
  printf("format: source <filename>\n");
  printf("description: read and executes commands from file <filename>\n");
}

void
Source::description()
{
  printf("reads and executes commands from file\n");
}

