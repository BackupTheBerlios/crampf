/*
 * Modifies keymapping
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "map.hh"
#include "../iosubsys/output.hh"

Map::Map( CommandMap* c ) : Command()
{
  cmap = c;
}

void
Map::doit( const std::string &s )
{
  if (s=="list" || s=="all" || s=="show" || s=="") {
    output->printf("---Special-Keys-(always-available)---\n");
    output->printf("key ':' -> enter command\n");
    output->printf("key '/' -> search forward\n");
    output->printf("key '?' -> search backward\n");
    output->printf("---Keymap-(user-definable)---\n");
    for (std::map<char,std::string>::const_iterator it = cmap->keymap.begin();
        it != cmap->keymap.end(); it++)
     output->printf("key '%c' -> '%s'\n",it->first,it->second.c_str()); 
  } else {
    char functionname[255]; 
    unsigned int keyname_numeric;
    char keyname;
    if (sscanf(s.c_str(),"\\%o%*[ \t=]%[^\n]",
          &keyname_numeric,functionname)==2)
	keyname = keyname_numeric;
    else if (sscanf(s.c_str(),"%c%*[ \t=]%[^\n]",
		&keyname,functionname)!=2)  
	throw std::string("map: parsing error");
    cmap->setKey(keyname, functionname);
  }
}

void
Map::help( const std::string &s ) const
{
  output->printf("format: map <keyname> <command> [<parameter>]\n");
  output->printf("    or: map\n");
  output->printf("description: binds the inputcharacter <keyname> to the\n");
  output->printf("command <commandname>. Parameter to the specified command\n");
  output->printf("may be optionally given with <parameter>\n");
  output->printf("<keyname> can be a single letter or an octal value in the\n");
  output->printf("form of \\xxx\n");
}


void 
Map::description() const
{
  output->printf("binds commands to keystrokes\n");
}
