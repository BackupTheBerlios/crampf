//
// One class for each command. doit method called by commandmap
//

#ifndef SET
#define SET SET

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Set : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif
