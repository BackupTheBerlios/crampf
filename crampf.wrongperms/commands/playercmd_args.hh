//
// $Id: playercmd_args.hh,v 1.2 2000/07/16 23:00:57 logic Exp $
//

#ifndef PLAYERCMD_ARGS
#define PLAYERCMD_ARGS PLAYERCMD_ARGS

#include "../command.hh"
#include <string>

class PlayerCMD_Args : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

