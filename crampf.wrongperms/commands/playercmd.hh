//
// $Id: playercmd.hh,v 1.1 2000/03/19 09:00:25 logic Exp $
//

#ifndef playercmd
#define playercmd playercmd

#include "../command.hh"
#include <string>

class PlayerCMD : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

