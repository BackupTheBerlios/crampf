#include "stdout.hh"
#include "../config.h"

StdOutput::StdOutput() : OutputObject( "stdout" )
{
      printf( "welcome to the crampf %s\n", VERSION );
}

void
StdOutput::flush()
{
      while( !empty() ){
	  fputs( front().c_str(), stdout );
	  pop();
      }
}

void
StdOutput::configure( const std::string &s )
{
      /* TODO */
      throw std::string( "stdout module cannot be configured\n" );
}

void
StdOutput::help( const std::string &s ) const
{
      output->printf( "stdout module cannot be configured\n" );
}

void
StdOutput::description() const
{
      output->printf( "sends all output to stdout\n" );
}

StdOutput::~StdOutput()
{
      fputs( "Thank you for using crampf!\n", stdout );
}
