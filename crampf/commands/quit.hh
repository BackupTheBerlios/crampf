//
// One class for each command. doit method called by commandmap
//

#ifndef quit
#define quit

#include "../version_info.hh"
#include <string>
#include "../command.hh"

class Quit : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif
