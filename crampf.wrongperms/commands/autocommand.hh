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
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
    bool evtcb( const string &msg );
};

#endif
