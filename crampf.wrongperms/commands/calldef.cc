#include "define.hh"
#include "../commandmap.hh"
#include <string>
#include <stdio.h>
#include <vector>
#include <map>
#include "calldef.hh"
#include "../iosubsys/output.hh"

CallDef::CallDef( CommandMap* c )
{
  cmap = c;
}

void
CallDef::doit( const std::string &s )
{
  char c[s.size()];
  sscanf(s.c_str(),"%s",c);
  std::string args = CommandMap::args( s );
  if (cmap->defmap.count(c)==0) {
    output->printf("calldef: not a macro\n");
    return;
  } else 
    execute(c,args);
}

void 
CallDef::help( const std::string &s ) const
{
  output->printf("format: calldef <macroname>\n");
  output->printf("description: explicitly call the macro <macroname>\n");
  output->printf("see also: define, map\n");
}

void
CallDef::description() const
{
  output->printf("explicitly call the macro <macroname>\n");
}

void
CallDef::execute( const std::string &macro, const std::string &args )
{
  for (std::vector<std::string>::const_iterator it = cmap->defmap[macro].begin();
      it != cmap->defmap[macro].end(); it++){
      std::vector<std::string>::const_iterator at = it;
      at++;
      if( at == cmap->defmap[macro].end() )
	  /* add argument to last command */
	  (*cmap)[(*it)+" "+args];
      else
	  (*cmap)[(*it)];
  }
}

