#include <string>
#include "../command.hh"
#include "../command.hh"
#include "../commandmap.hh"
#include "define.hh"
#include <vector>
#include <stdio.h>
#include <string.h>
#include "../iosubsys/output.hh"

Define::Define( CommandMap* c )
{
  cmap = c;
}

void
Define::doit( const std::string &s )
{
  if (s.empty())
    showdefines();
  else if ((signed)(s.find('='))==-1) {
    if (cmap->defmap.count(s))
      showdefine(s);
    else
      throw std::string("no such macro");
  } else
      adddef(s);
}

void
Define::help( const std::string &s ) const
{
  output->printf("format: define\n");
  output->printf("    or: define <macroname>\n");
  output->printf("    or: define <macroname>=<comando> [; <commando> [; ...] ]\n");
  output->printf("description: list all macro, contents of macro <macroname>\n");
  output->printf("or define a macro.\n");
  output->printf("see also: calldef\n");
}

void
Define::description() const
{
  output->printf("gets/sets definition (macros)\n");
}

void
Define::adddef( std::string s )
{
  char pstr[s.size()];
  sscanf(s.c_str(),"%[^=]",pstr);
  std::string defname = pstr;
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
Define::showdefine( const std::string &s ) const
{
  output->printf("define: %s\n",s.c_str());
  for (std::vector<std::string>::const_iterator it = cmap->defmap[s].begin();
      it != cmap->defmap[s].end(); it++)
    output->printf("\t%s\n",it->c_str());
}

void
Define::showdefines() const
{
  output->printf("--defined-macros--\n");
  for (std::map<std::string,std::vector<std::string> >::const_iterator it = cmap->defmap.begin();
      it != cmap->defmap.end(); it++)
    output->printf("\t%s\n",it->first.c_str());
}
    
