//
// CommandoMap -- maps Functionsnames/Hotkeys -> Functions
//

#ifndef COMMANDMAP
#define COMMANDMAP COMMANDMAP

#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include "command.hh"

class CommandMap {
  public:
    CommandMap();
    ~CommandMap();
    void operator[](string cmd);
    void setKey(char key, string cmd);
    void help(string cmd);
    void operator[](char key);
    map<string, Command*> cmdmap;
    map<char, string> keymap;
    map< string , vector<string> > defmap;
    string searchstr;
  private:
    Command* findFirst( string c );
    string findFirstDef( string c );
    string arg0( string s );
    string args( string s );
    static unsigned int objcnt; /* bad hack: counts number of CommandMap-Entities
				    only first one initializes commands */
};
    
#endif

