//
// $Id: shuffle.hh,v 1.4 2000/07/16 23:00:57 logic Exp $
//

#ifndef SHUFFLE
#define SHUFFLE SHUFFLE

#include <string>
#include "../command.hh"

class Shuffle : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};
#endif

