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

