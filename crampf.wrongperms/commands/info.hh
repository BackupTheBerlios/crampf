//
// One class for each command. doit method called by commandmap
//

#ifndef INFO_HH
#define INFO_HH INFO_HH

#include <string>
#include "../command.hh"

class Info : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif
