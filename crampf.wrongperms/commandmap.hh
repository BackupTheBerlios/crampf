//
// CommandoMap -- maps Functionsnames/Hotkeys -> Functions
//

#ifndef commandmap
#define commandmap

#include <string>
#include <map>
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
  private:
    string arg0( string s );
    string args( string s );
};
    
#endif

