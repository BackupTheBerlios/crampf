#include "../command.hh"
#include "../config.h"
#include "echo.hh"
#include <string>
#include <stdio.h>

/* TODO implement some %s directives (e.g. version number, current songname,
				      current trackno, etc.)
 */

void
Echo::doit( const string &s )
{
  printf( "%s\n", s.c_str() );
}

void
Echo::help( const string &s ) const
{
  printf("format: echo <text>\n");
  printf("description: prints out given arguments\n");
}

void 
Echo::description() const
{
  printf("prints out given arguments\n");
}