//
// $Id: playercmd_args.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef PLAYERCMD_ARGS_HH
#define PLAYERCMD_ARGS_HH PLAYERCMD_ARGS_HH

#include "../command.hh"
#include <string>

class PlayerCMD_Args : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

