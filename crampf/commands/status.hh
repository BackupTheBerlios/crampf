//
// One class for each command. doit method called by commandmap
//

#ifndef STATUS
#define STATUS STATUS

#include <string>
#include "../command.hh"

class Status : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif
