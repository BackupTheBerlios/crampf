/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "autocommand.hh"
#include "../autocmd.hh"
#include "../options.hh"
#include "../debug.hh"
#include "../iosubsys/output.hh"

Autocommand::Autocommand()
{
  doit( "start status" );
  doit( "stop next" );
}

void
Autocommand::doit( const std::string &s )
{
  unsigned int p = s.find(" ");
  if( (signed)p == -1 || s.empty() ){
      output->printf( "current autocommands:\n" );
      for( std::map<std::string,std::string>::const_iterator it = actionmap.begin();
	      it != actionmap.end(); it++ )
	  output->printf( "\t%s\t%s\n", it->first.c_str(), it->second.c_str() );
      return;
  }
  std::string evt = s.substr(0,s.find(" "));
  std::string act = s.substr(s.find(" ")+1);
  if( autocmdmap.count( evt ) != 1 ){
      output->printf( "autocmdmap: no such event %s\n", evt.c_str() );
      return;
  }
  printdebug( "autocmdmap: registered command '%s' on event '%s'\n",
	  act.c_str(), evt.c_str() );
  if( !actionmap.count( evt ) ) /* did we already register this event? */
      autocmdmap[evt].registerCB( callback(*this,&Autocommand::evtcb) );
  actionmap[evt] = act;
}

bool
Autocommand::evtcb( const std::string &event )
{
  printdebug( "autocmdmap: received event %s\n", event.c_str() );
  if( actionmap.count( event ) != 1 ){
      output->printf( "autocmdmap: received unregistered event %s\n", event.c_str() );
      return false;
  }
  printdebug( "autocmdmap: executing command '%s'\n", actionmap[event].c_str() );
  opts->cmdmap[ actionmap[event] ];
  return true;
}

void
Autocommand::help( const std::string &s ) const
{
  output->printf("format: autocommand [<Event> <Action>]\n");
  output->printf("description: command action is executed whenever event occurs\n");
  output->printf("Event may be one of:\n" );
  for( AutocmdMap::const_iterator it = autocmdmap.begin();
	  it != autocmdmap.end(); it++ )
      output->printf( "\t%s\t- %s\n", it->first.c_str(), it->second.description.c_str() );
  output->printf("Action may be any valid command\n");
  output->printf("If no arguments given the current autocommands are shown.\n");
}

void 
Autocommand::description() const
{
  output->printf("bind commands on events\n");
}
