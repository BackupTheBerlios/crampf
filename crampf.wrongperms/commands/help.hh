//
// One class for each command. doit method called by commandmap
//

#ifndef help
#define help help

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Help : public Command {
  public:
    Help( CommandMap* c);
    void doit( string s );
    void help( string s );
  private:
    CommandMap* cmap;
};

#endif
