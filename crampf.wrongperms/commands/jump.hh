//
// $Id: jump.hh,v 1.5 2002/06/01 17:27:37 logic Exp $
//

#ifndef JUMP_HH
#define JUMP_HH JUMP_HH

#include <string>
#include "../command.hh"

class Jump : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

