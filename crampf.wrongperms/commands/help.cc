/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "help.hh"
#include "../iosubsys/output.hh"

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
    output->printf("crampf readline interface online help\n");
    output->printf("-------------------------------------\n");
    output->printf("available commands:\n");
    for (std::map<std::string,Command*>::const_iterator it = cmap->cmdmap.begin();
        it != cmap->cmdmap.end(); it++) {
      for (int len = output->printf("\t%s",it->first.c_str()); len<20; len++)
        output->printf(" ");
      it->second->description();
    }
    output->printf("for detailed help type `:help <commandname>'\n");
  }
}

void
Help::help( const std::string &s ) const
{
  output->printf("format: help [<command>]\n");
  output->printf("description: list all commands avaible, or specific help\n");
  output->printf("on command <command>.\n");
}

void 
Help::description() const
{
  output->printf("interactive help command\n");
}
