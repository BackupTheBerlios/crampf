//
// $Id: randomorder.hh,v 1.2 2000/07/16 23:00:57 logic Exp $
//

#ifndef RANDOMORDER
#define RANDOMORDER RANDOMORDER

#include "../command.hh"
#include <string>

class RandomOrder : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

