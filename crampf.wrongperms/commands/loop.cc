#include "../command.hh"
#include "../options.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "loop.hh"

extern struct options* opts;

void
Loop::doit( const std::string &s )
{
  if (s.empty()) {
    printf("loop: %d\n",opts->loop);
  } else {
    opts->loop=atoi(s.c_str());
  }
}

void
Loop::help( const std::string &s ) const
{
  printf("format: loop <number>\n");
  printf("description: whenever the playlist reaches the end the value\n");
  printf("of loop is decreased by one. If its value is zero at this moment\n");
  printf("the playback is stopped.\n");
  printf("A negative value (e.g. -1) means loop forever.\n");
}

void
Loop::description() const
{
  printf("controls looping behaviour\n");
}
