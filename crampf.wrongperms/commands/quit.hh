//
// One class for each command. doit method called by commandmap
//

#ifndef QUIT
#define QUIT QUIT

#include <string>
#include "../command.hh"

class Quit : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif
