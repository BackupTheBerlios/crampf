//
// One class for each command. doit method called by commandmap
//

#ifndef HELP
#define HELP HELP

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Help : public Command {
  public:
    Help( CommandMap* c);
    void doit( string s );
    void help( string s );
    void description();
  private:
    CommandMap* cmap;
};

#endif
