#include "define.hh"
#include "../commandmap.hh"
#include <string>
#include <stdio.h>
#include <vector>
#include <map>
#include "calldef.hh"

CallDef::CallDef( CommandMap* c )
{
  cmap = c;
}

void
CallDef::doit( string s )
{
  char c[s.size()];
  sscanf(s.c_str(),"%s",c);
  if (cmap->defmap.count(c)==0) {
    printf("calldef: not a macro\n");
    return;
  } else 
    execute(c);
}

void 
CallDef::help( string s )
{
  printf("format: calldef <macroname>\n");
  printf("description: explicitly call the macro <macroname>\n");
}

void
CallDef::description()
{
  printf("explicitly call the macro <macroname>\n");
}

void
CallDef::execute( string s )
{
  for (vector<string>::iterator it = cmap->defmap[s].begin();
      it != cmap->defmap[s].end(); it++)
    (*cmap)[(*it)];
}

