#include "../config.hh"
#include <string>
#include <stdio.h>
#include "playercmd.hh"

extern struct options* opts;

void
PlayerCMD::doit( string s )
{
  if (s.empty()) {
    printf("playercmd: %s\n",opts->playercmd.c_str());
    return;
  } else 
    opts->playercmd=s;
}

void
PlayerCMD::help( string s )
{
  printf("format: playercmd [<playercmd>]\n");
  printf("description: gets/set the mp3player command.\n");
  printf("USE WITH CAUTION!\n");
}

void
PlayerCMD::description()
{
  printf("gets/set the mp3player command.\n");
}
