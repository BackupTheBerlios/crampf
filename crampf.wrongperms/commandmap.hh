//
// CommandoMap -- maps Functionsnames/Hotkeys -> Functions
//

#ifndef COMMANDMAP_HH
#define COMMANDMAP_HH COMMANDMAP_HH

#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include "command.hh"

class CommandMap {
  public:
    CommandMap();
    ~CommandMap();
    void operator[](const string &cmd);
    void setKey(char key, const string &cmd);
    void help(const string &cmd);
    void operator[](char key);
    map<string, Command*> cmdmap;
    map<char, string> keymap;
    map< string , vector<string> > defmap;
    string searchstr;
  private:
    Command* findFirst( const string &c ) const;
    string findFirstDef( const string &c ) const;
    string arg0( string s ) const;
    string args( string s ) const;
    vector<string> splitCommands( string s );
    static unsigned int objcnt; /* bad hack: counts number of CommandMap-Entities
				    only first one initializes commands */
};
    
#endif

