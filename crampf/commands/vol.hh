//
// One class for each command. doit method called by commandmap
//

#ifndef vol
#define vol

#include "../version_info.hh"
#include <string>
#include "../command.hh"

class Vol : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif
