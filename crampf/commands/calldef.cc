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
  if (cmap->defmap.count(c)==0) {
    output->printf("calldef: not a macro\n");
    return;
  } else 
    execute(c);
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
CallDef::execute( const std::string &s )
{
  for (std::vector<std::string>::const_iterator it = cmap->defmap[s].begin();
      it != cmap->defmap[s].end(); it++) 
    (*cmap)[(*it)];
}

