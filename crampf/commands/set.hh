//
// One class for each command. doit method called by commandmap
//

#ifndef set
#define set

#include "../version_info.hh"
#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Set : public Command {
  public:
    void doit( string s );
    void help( string s );
  private:
};

#endif
