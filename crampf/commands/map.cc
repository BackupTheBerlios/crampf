/*
 * Modifies keymapping
 */


#include "../version_info.hh"
#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "map.hh"

Map::Map( CommandMap* c ) : Command()
{
  cmap = c;
}

void
Map::doit( string s )
{
  if (s=="list" || s=="all" || s=="show" || s=="") {
    printf("---Special-Keys-(always-avaible)---\n");
    printf("key ':' -> enter command\n");
    printf("key '/' -> search forward\n");
    printf("key '?' -> search backward\n");
    printf("---Keymap-(user-definable)---\n");
    for (map<char,string>::iterator it = cmap->keymap.begin();
        it != cmap->keymap.end(); it++)
     printf("key '%c' -> '%s'\n",it->first,it->second.c_str()); 
  } else {
    char functionname[255]; 
    char keyname;
    if (sscanf(s.c_str(),"\\%o%*[ \t=]%[^\n]",
          &keyname,functionname)!=2)
      if (sscanf(s.c_str(),"%c%*[ \t=]%[^\n]",
            &keyname,functionname)!=2)  
        throw string("map: parsing error");
    cmap->setKey(keyname, functionname);
  }
}

void
Map::help( string s )
{
  printf("format: map <keyname> <command> [<parameter>]\n");
  printf("    or: map\n");
  printf("description: binds the inputcharacter <keyname> to the\n");
  printf("command <commandname>. Parameter to the specified command\n");
  printf("may be optionally given with <parameter>\n");
  printf("<keyname> can be a single letter or an octal value in the\n");
  printf("form of \\xxx\n");
}


void 
Map::description()
{
  printf("binds commands to keystrokes\n");
}
