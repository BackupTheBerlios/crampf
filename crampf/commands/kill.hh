//
// $Id: kill.hh,v 1.2 2002/06/01 17:27:37 logic Exp $
//

#ifndef KILL_HH
#define KILL_HH KILL_HH

#include "../command.hh"
#include <string>

class Kill : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

