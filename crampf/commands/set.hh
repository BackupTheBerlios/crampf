//
// One class for each command. doit method called by commandmap
//

#ifndef set
#define set

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Set : public Command {
  public:
    Set( CommandMap* c );
    void doit( string s );
    void help( string s );
  private:
    CommandMap* cmap;
};

#endif
