#include "../command.hh"
#include "../options.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "loop.hh"
#include "../iosubsys/output.hh"

void
Loop::doit( const std::string &s )
{
  if (s.empty()) {
    output->printf("loop: %d\n",opts->loop);
  } else {
    opts->loop=atoi(s.c_str());
  }
}

void
Loop::help( const std::string &s ) const
{
  output->printf("format: loop <number>\n");
  output->printf("description: whenever the playlist reaches the end the value\n");
  output->printf("of loop is decreased by one. If its value is zero at this moment\n");
  output->printf("the playback is stopped.\n");
  output->printf("A negative value (e.g. -1) means loop forever.\n");
}

void
Loop::description() const
{
  output->printf("controls looping behaviour\n");
}
