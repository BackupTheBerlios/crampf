//
// One class for each command. doit method called by commandmap
//

#ifndef AUTOCOMMAND_HH
#define AUTOCOMMAND_HH AUTOCOMMAND_HH

#include <string>
#include <map>
#include "../command.hh"

class Autocommand : public Command {
  private:
      map<string,string> actionmap;
  public:
    Autocommand();
    void doit( string s );
    void help( string s );
    void description();
    bool evtcb( const string &msg );
};

#endif
