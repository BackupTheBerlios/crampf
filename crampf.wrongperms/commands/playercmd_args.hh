//
// $Id: playercmd_args.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
//

#ifndef PLAYERCMD_ARGS_HH
#define PLAYERCMD_ARGS_HH PLAYERCMD_ARGS_HH

#include "../command.hh"
#include <string>

class PlayerCMD_Args : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

