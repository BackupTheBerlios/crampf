//
// $Id: playercmd.hh,v 1.2 2000/07/16 23:00:57 logic Exp $
//

#ifndef PLAYERCMD
#define PLAYERCMD PLAYERCMD

#include "../command.hh"
#include <string>

class PlayerCMD : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

