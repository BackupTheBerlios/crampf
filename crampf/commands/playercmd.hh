//
// $Id: playercmd.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef PLAYERCMD_HH
#define PLAYERCMD_HH PLAYERCMD_HH

#include "../command.hh"
#include <string>

class PlayerCMD : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

