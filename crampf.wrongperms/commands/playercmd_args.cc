#include "../config.hh"
#include "playercmd_args.hh"
#include <string>
#include <stdio.h>

extern struct options* opts;

void
PlayerCMD_Args::doit( string s )
{
  if (s.empty()) {
    printf("playercmd_args: %s\n",opts->playercmd_args.c_str());
    return;
  } else {
    opts->playercmd_args=s;
  }
}

void
PlayerCMD_Args::help( string s )
{
  printf("format: playercmd_args [<args>]\n");
  printf("description: gets/sets mp3play arguments.\n");
  printf("USE WITH CAUTION!\n");
}

void
PlayerCMD_Args::description()
{
  printf("gets/sets mp3play arguments.\n");
}
