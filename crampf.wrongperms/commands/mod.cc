/*
 * Modifies keymapping
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "../iosubsys/output.hh"
#include "../iosubsys/input.hh"
#include "mod.hh"
#include "../module.hh"

void
Mod::doit( const std::string &s )
{
  if (s=="list" || s=="all" || s=="show" || s=="") {
      output->printf( "available modules:\n" );
      for( Modules::const_iterator it = modules->begin();
	      it != modules->end(); it ++ ){
	  output->printf( "\t%-10s ", it->first.c_str() );
	  it->second->description();
      }
      return;
  } else
      for( Modules::const_iterator it = modules->begin();
	      it != modules->end(); it ++ )
	  if( s.find( " " ) == -1 ){
	      if( it->first.find( s ) == 0 ){
		  it->second->configure( "" );
		  return;
	      }
	  } else
	      if( it->first.find( s.substr( 0, s.find( " " ) ) ) == 0 ){
		  std::string args = CommandMap::args( s );
		  it->second->configure( args );
		  return;
	      }
  output->printf( "unknown module\n" );
}

void
Mod::help( const std::string &s ) const
{
      if( s.empty() ){
	  output->printf("format: module <modulename> <option> [<value...>]\n");
	  output->printf("    or: module\n");
	  output->printf("    or: module <modulename>\n");
	  output->printf("description: If no argument is given all currently available\n" );
	  output->printf("modules are listed. If only the <modulename> is given then the\n" );
	  output->printf("configuration of this module is printed. To get a help on the a\n" );
	  output->printf("module enter 'help module <modulename>'.\n" );
      } else {
	  for( Modules::const_iterator it = modules->begin();
		  it != modules->end(); it ++ )
	      if( s.find( " " ) == -1 ){
		  if( it->first.find( s ) == 0 ){
		      it->second->help( "" );
		      return;
		  }
	      } else {
		  std::string args = CommandMap::args( s );
		  if( it->first.find( s.substr( 0, s.find( " " ) ) ) == 0 ){
		      it->second->help( args );
		      return;
		  }
	      }
      }
}


void 
Mod::description() const
{
  output->printf("configure modules\n");
}
