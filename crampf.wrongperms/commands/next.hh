//
// One class for each command. doit method called by commandmap
//

#ifndef next
#define next

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Next : public Command {
  public:
    void doit( string s );
    void help( string s );
};
#endif
