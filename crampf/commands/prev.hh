//
// One class for each command. doit method called by commandmap
//

#ifndef prev
#define prev

#include <string>
#include "../command.hh"

class Prev : public Command {
  public:
    void doit( string s );
    void help( string s );
};

#endif
