#include "output.hh"
#include "../config.h"
#include <stdarg.h>

int
Output::printf( const char *fmt, ... )
{
      static char buf[BUFSIZ];
      va_list ap;
      va_start( ap, fmt );
      int res = vsnprintf( buf, BUFSIZ, fmt, ap );
      va_end( ap );
      for( iterator it = begin(); it != end(); it++ )
	  (*it)->push( buf );
      return res;
}

void
Output::flush()
{
      for( iterator it = begin(); it != end(); it++ )
	  (*it)->flush();
}

Output::~Output()
{
      for( iterator it = begin(); it != end(); it++ )
	  delete *it;
}

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
