//
// $Id: playercmd_args.hh,v 1.1 2000/03/19 09:00:25 logic Exp $
//

#ifndef playercmd_args
#define playercmd_args playercmd_args

#include "../command.hh"
#include <string>

class PlayerCMD_Args : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

