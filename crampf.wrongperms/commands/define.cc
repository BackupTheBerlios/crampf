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
Define::doit( const string &s )
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
Define::help( const string &s ) const
{
  printf("format: define\n");
  printf("    or: define <macroname>\n");
  printf("    or: define <macroname>=<comando> [; <commando> [; ...] ]\n");
  printf("description: list all macro, contents of macro <macroname>\n");
  printf("or define a macro.\n");
  printf("see also: calldef\n");
}

void
Define::description() const
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
Define::showdefine( const string &s ) const
{
  printf("define: %s\n",s.c_str());
  for (vector<string>::const_iterator it = cmap->defmap[s].begin();
      it != cmap->defmap[s].end(); it++)
    printf("\t%s\n",it->c_str());
}

void
Define::showdefines() const
{
  printf("--defined-macros--\n");
  for (map<string,vector<string> >::const_iterator it = cmap->defmap.begin();
      it != cmap->defmap.end(); it++)
    printf("\t%s\n",it->first.c_str());
}
    
