//
// $Id: jump.hh,v 1.4 2000/07/16 23:00:56 logic Exp $
//

#ifndef JUMP
#define JUMP JUMP

#include <string>
#include "../command.hh"

class Jump : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

