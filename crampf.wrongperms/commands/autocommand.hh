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
      std::map<std::string,std::string> actionmap;
  public:
    Autocommand();
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
    bool evtcb( const std::string &msg );
};

#endif
