/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "set.hh"

Set::Set( CommandMap* c ) : Command()
{
  cmap = c;
}

void
Set::doit( string s )
{
  if (s=="list") {
    printf("current keybindings:\n");
    for (map<char,string>::iterator it = cmap->keymap.begin();
        it != cmap->keymap.end(); it++)
     printf("key '%c' -> '%s'\n",it->first,it->second.c_str()); 
  } else if (s.find("key")==0) {
    char functionname[255]; 
    char keyname;
    if (sscanf(s.c_str(),"key%*[ \t]\\%o%*[ \t]%[^\n]",
          &keyname,functionname)!=2)
      if (sscanf(s.c_str(),"key%*[ \t]%c%*[ \t]%[^\n]",
            &keyname,functionname)!=2)  
        throw string("set: parsing error");
    cmap->setKey(keyname, functionname);
  }
}

void
Set::help( string s )
{
  printf("format:\t\"set key <keyname> <command> [<parameters>]\"\n");
  printf("binds the inputcharacter <keyname> to command <command>\n");
  printf("optional parameters may be specified\n");
  printf("keyname may be an ascii character or its octal value\n");
  printf("in the notation \\xxx\n");
  printf("to show current bindings enter `set list'\n");
}

