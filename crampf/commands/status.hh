//
// One class for each command. doit method called by commandmap
//

#ifndef status
#define status

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Status : public Command {
  public:
    void doit( string s );
    void help( string s );
};

#endif
