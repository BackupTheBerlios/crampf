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
    void operator[](const std::string &cmd);
    void help(const std::string &cmd);
    std::map<std::string, Command*> cmdmap;
    std::map< std::string , std::vector<std::string> > defmap;
    std::string searchstr;
  private:
    Command* findFirst( const std::string &c ) const;
    std::string findFirstDef( const std::string &c ) const;
    std::vector<std::string> splitCommands( std::string s );
    static unsigned int objcnt; /* bad hack: counts number of CommandMap-Entities
				    only first one initializes commands */
  public:
    /* generic parser helpers, arg0 returns only first word, args returns the rest */
    static std::string arg0( std::string s );
    static std::string args( std::string s );
};
    
#endif

