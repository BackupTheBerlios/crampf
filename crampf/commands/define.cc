#include <string>
#include "../command.hh"
#include "../command.hh"
#include "../commandmap.hh"
#include "define.hh"
#include <vector>
#include <stdio.h>
#include <string.h>

Define::Define( CommandMap* c )
{
  cmap = c;
}

void
Define::doit( string s )
{
  if (s.empty())
    showdefines();
  else if (s.find('=')==-1) {
    if (cmap->defmap.count(s))
      showdefine(s);
    else
      printf("no such macro\n");
  } else
      adddef(s);
}

void
Define::help( string s )
{
  printf("format: define\n");
  printf("    or: define <macroname>\n");
  printf("    or: define <macroname>=<comando> [; <commando> [; ...] ]\n");
  printf("description: list all macro, contents of macro <macroname>\n");
  printf("or define a macro.\n");
}

void
Define::description()
{
  printf("gets/sets definition (macros)\n");
}

void
Define::adddef(string s)
{
  char pstr[s.size()];
  sscanf(s.c_str(),"%[^=]",pstr);
  string defname = pstr;
  s.erase(0,s.find('=')+1);
  if (cmap->defmap.count(defname)>0) {
    cmap->defmap[defname].erase(cmap->defmap[defname].begin(),cmap->defmap[defname].end());
  }
  while (sscanf(s.c_str(),"%[^;]",pstr)>0) {
    cmap->defmap[defname].push_back(pstr);
    s.erase(0,strlen(pstr)+1);
  }
}

void
Define::showdefine( string s )
{
  printf("define: %s\n",s.c_str());
  for (vector<string>::iterator it = cmap->defmap[s].begin();
      it != cmap->defmap[s].end(); it++)
    printf("\t%s\n",it->c_str());
}

void
Define::showdefines()
{
  printf("--defined-macros--\n");
  for (map<string,vector<string> >::iterator it = cmap->defmap.begin();
      it != cmap->defmap.end(); it++)
    printf("macros: %s\n",it->first.c_str());
}
    
