//
// One class for each command. doit method called by commandmap
//

#ifndef VOL
#define VOL VOL

#include <string>
#include "../command.hh"

class Vol : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif
