/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "../player.hh"
#include "../playlist.hh"
#include "help.hh"

extern Playlist* plist;

Help::Help( CommandMap* c )
{
  cmap = c;
}

void
Help::doit( string s )
{
  if (!s.empty())
    cmap->help(s);
  else {
    printf("crampf readline interface online help\n");
    printf("-------------------------------------\n");
    printf("avaible commands:\n");
    for (map<string,Command*>::iterator it = cmap->cmdmap.begin();
        it != cmap->cmdmap.end(); it++)
      printf("\t%s\n",it->first.c_str());
    printf("for detailed help type `:help <commandname>'\n");
  }
}

void
Help::help( string s )
{
  printf("help [command] -- displays short help (on command)\n");
}

