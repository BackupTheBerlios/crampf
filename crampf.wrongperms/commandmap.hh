//
// CommandoMap -- maps Functionsnames/Hotkeys -> Functions
//

#ifndef commandmap
#define commandmap

#include "version_info.hh"
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
  private:
    Command* findFirst( string c );
    string findFirstDef( string c );
    string arg0( string s );
    string args( string s );
};
    
#endif

