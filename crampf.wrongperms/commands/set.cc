/*
 * Here are all commands defined
 */


#include <string>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../commandmap.hh"
#include "../player.hh"
#include "../playlist.hh"
#include "set.hh"

extern Playlist* plist;

Set::Set( CommandMap* c ) : Command()
{
  cmap = c;
}

void
Set::doit( string s )
{
  char functionname[255]; 
  char keyname;
  if (sscanf(s.c_str(),"key%*[ \t]%c%*[ \t]%[^\n]",&keyname,functionname)!=2) 
    if (sscanf(s.c_str(),"key%*[ \t]'%c'%*[ \t]%[^\n]",
          &keyname,functionname)!=2)
      throw string("set: parsing error");
  cmap->setKey(keyname, functionname);
}

void
Set::help( string s )
{
  printf("format:\t\"set key <keyname> <command> [<parameters>]\"\n");
  printf("or \t\"set key '<keyname>' <command> [<parameters>]\"\n");
  printf("binds the inputcharacter <keyname> to command <command>\n");
  printf("optional parameters may be specified\n");
}

