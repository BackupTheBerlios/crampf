/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "help.hh"

Help::Help( CommandMap* c )
{
  cmap = c;
}

void
Help::doit( const std::string &s )
{
  if (!s.empty())
    cmap->help(s);
  else {
    printf("crampf readline interface online help\n");
    printf("-------------------------------------\n");
    printf("available commands:\n");
    for (std::map<std::string,Command*>::const_iterator it = cmap->cmdmap.begin();
        it != cmap->cmdmap.end(); it++) {
      for (int len = printf("\t%s",it->first.c_str()); len<20; len++)
        printf(" ");
      it->second->description();
    }
    printf("for detailed help type `:help <commandname>'\n");
  }
}

void
Help::help( const std::string &s ) const
{
  printf("format: help [<command>]\n");
  printf("description: list all commands avaible, or specific help\n");
  printf("on command <command>.\n");
}

void 
Help::description() const
{
  printf("interactive help command\n");
}
