/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "autocommand.hh"
#include "../autocmd.hh"
#include "../config.hh"
#include "../debug.hh"

extern struct options* opts;

Autocommand::Autocommand()
{
  doit( "next next" );
}

void
Autocommand::doit( const string &s )
{
  unsigned int p = s.find(" ");
  if( (signed)p == -1 || s.empty() ){
      printf( "current autocommands:\n" );
      for( map<string,string>::const_iterator it = actionmap.begin();
	      it != actionmap.end(); it++ )
	  printf( "\t%s\t%s\n", it->first.c_str(), it->second.c_str() );
      return;
  }
  string evt = s.substr(0,s.find(" "));
  string act = s.substr(s.find(" ")+1);
  if( autocmdmap.count( evt ) != 1 ){
      printf( "autocmdmap: no such event %s\n", evt.c_str() );
      return;
  }
  printdebug( "autocmdmap: registered command '%s' on event '%s'\n",
	  act.c_str(), evt.c_str() );
  if( !actionmap.count( evt ) ) /* did we already register this event? */
      autocmdmap[evt].registerCB( callback(*this,&Autocommand::evtcb) );
  actionmap[evt] = act;
}

bool
Autocommand::evtcb( const string &event )
{
  printdebug( "autocmdmap: received event %s\n", event.c_str() );
  if( actionmap.count( event ) != 1 ){
      printf( "autocmdmap: received unregistered event %s\n", event.c_str() );
      return false;
  }
  printdebug( "autocmdmap: executing command '%s'\n", actionmap[event].c_str() );
  opts->cmdmap[ actionmap[event] ];
  return true;
}

void
Autocommand::help( const string &s ) const
{
  printf("format: autocommand [<Event> <Action>]\n");
  printf("description: command action is executed whenever event occurs\n");
  printf("Event may be one of:\n" );
  for( AutocmdMap::const_iterator it = autocmdmap.begin();
	  it != autocmdmap.end(); it++ )
      printf( "\t%s\t- %s\n", it->first.c_str(), it->second.description.c_str() );
  printf("Action may be any valid command\n");
  printf("If no arguments given the current autocommands are shown.\n");
}

void 
Autocommand::description() const
{
  printf("bind commands on events\n");
}
