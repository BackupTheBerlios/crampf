#include "../command.hh"
#include "../commandmap.hh"
#include <string>
#include "source.hh"
#include "../file.hh"
#include "../iosubsys/output.hh"

Source::Source( CommandMap* c )
{
  cmap = c;
}

void
Source::doit( const std::string &s )
{
  File f(s);
  std::string cmd;
  while (1) {
    try {
      cmd = ++f;
      (*cmap)[cmd];
    } catch (std::string error) {
      if (error=="end of file")
        return;
      output->printf("source(%s,line %d): %s \"%s\"\n", s.c_str(),f.linenum(),error.c_str(), cmd.c_str());
    }
  }
}

void
Source::help( const std::string &s ) const
{
  output->printf("format: source <filename>\n");
  output->printf("description: read and executes commands from file <filename>\n");
}

void
Source::description() const
{
  output->printf("reads and executes commands from file\n");
}

