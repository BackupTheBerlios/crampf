//
// One class for each command. doit method called by commandmap
//

#ifndef quit
#define quit

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Quit : public Command {
  public:
    void doit( string s );
    void help( string s );
};

#endif
