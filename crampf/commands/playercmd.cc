#include "../config.hh"
#include <string>
#include <stdio.h>
#include "playercmd.hh"

extern struct options* opts;

void
PlayerCMD::doit( const std::string &s )
{
  if (s.empty()) {
    printf("playercmd: %s\n",opts->playercmd.c_str());
    return;
  } else 
    opts->playercmd=s;
}

void
PlayerCMD::help( const std::string &s ) const
{
  printf("format: playercmd [<playercmd>]\n");
  printf("description: gets/set the mp3player command.\n");
  printf("see also: playercmd_args\n");
  printf("USE WITH CAUTION!\n");
}

void
PlayerCMD::description() const
{
  printf("gets/set the mp3player command.\n");
}
