//
// $Id: playercmd_args.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef PLAYERCMD_ARGS_HH
#define PLAYERCMD_ARGS_HH PLAYERCMD_ARGS_HH

#include "../command.hh"
#include <string>

class PlayerCMD_Args : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

