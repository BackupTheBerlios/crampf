#include <string>
#include "filename.hh"
#include "../playlist.hh"
#include "../track.hh"
#include <stdio.h>
#include "../iosubsys/output.hh"

void
Filename::doit( const std::string &s )
{
  output->printf("filename: \"%s\"\n",(*(*plist)).filename().c_str());
}

void
Filename::help( const std::string &s ) const
{
  output->printf("format: filename\n");
  output->printf("description: shows full filename (with path) of current\n");
  output->printf("track.\n");
  output->printf("see also: status, info\n");
}

void
Filename::description() const
{
  output->printf("display full filename with path\n");
}

