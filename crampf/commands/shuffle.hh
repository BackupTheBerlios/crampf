//
// $Id: shuffle.hh,v 1.1 2000/03/16 12:48:37 logic Exp $
//

#ifndef shuffle
#define shuffle shuffle

#include <string>
#include "../command.hh"

class Shuffle : public Command {
  public:
    void doit( string s );
    void help( string s );
};
#endif

