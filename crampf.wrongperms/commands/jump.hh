//
// $Id: jump.hh,v 1.1 2000/03/16 12:48:37 logic Exp $
//

#ifndef jump
#define jump jump

#include <string>
#include "../command.hh"

class Jump : public Command {
  public:
    void doit( string s );
    void help( string s );
};

#endif

