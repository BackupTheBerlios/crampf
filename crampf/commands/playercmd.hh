//
// $Id: playercmd.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef PLAYERCMD_HH
#define PLAYERCMD_HH PLAYERCMD_HH

#include "../command.hh"
#include <string>

class PlayerCMD : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

