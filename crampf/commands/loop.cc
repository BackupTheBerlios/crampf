#include "../command.hh"
#include "../config.hh"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "loop.hh"

extern struct options* opts;

void
Loop::doit( string s )
{
  if (s.empty()) {
    printf("loop: %d\n",opts->loop);
  } else {
    opts->loop=atoi(s.c_str());
  }
}

void
Loop::help( string s )
{
  printf("format: loop <number>\n");
  printf("description: whenever the playlist reaches the end the value\n");
  printf("of loop is decreased by one. If its value is zero at this moment\n");
  printf("the playback is stopped.\n");
  printf("A negative value (e.g. -1) means loop forever.\n");
}

void
Loop::description()
{
  printf("controls looping behaviour\n");
}
