//
// One class for each command. doit method called by commandmap
//

#ifndef info
#define info

#include <string>
#include "../command.hh"

class Info : public Command {
  public:
    void doit( string s );
    void help( string s );
};

#endif
