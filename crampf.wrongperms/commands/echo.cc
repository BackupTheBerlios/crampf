#include "../command.hh"
#include "../config.h"
#include "echo.hh"
#include <string>
#include <stdio.h>
#include "../iosubsys/output.hh"

/* TODO implement some %s directives (e.g. version number, current songname,
				      current trackno, etc.)
 */

void
Echo::doit( const std::string &s )
{
  output->printf( "%s\n", s.c_str() );
}

void
Echo::help( const std::string &s ) const
{
  output->printf("format: echo <text>\n");
  output->printf("description: prints out given arguments\n");
}

void 
Echo::description() const
{
  output->printf("prints out given arguments\n");
}
