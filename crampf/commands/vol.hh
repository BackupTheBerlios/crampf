//
// One class for each command. doit method called by commandmap
//

#ifndef vol
#define vol

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Vol : public Command {
  public:
    void doit( string s );
    void help( string s );
};

#endif
