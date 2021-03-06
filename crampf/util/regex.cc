#include "regex.hh"
#include <string>
#include <regex.h>

RegEx::RegEx( const std::string &re, int cflags )
{
      cflags |= REG_NEWLINE | REG_NOSUB;
      int error = regcomp( &preg, re.c_str(), cflags );
      if (error != 0) {
	  char errmsg[REGEXP_MAXERRLEN];
	  regerror( error, &preg, errmsg, REGEXP_MAXERRLEN);
	  throw std::string(errmsg);
      }
}

RegEx::~RegEx()
{
      regfree( &preg );
}

bool 
RegEx::match( const std::string &s, int eflags ) const
{
      return (regexec( &preg, s.c_str(), 0, NULL, eflags )
	      != REG_NOMATCH);
}
