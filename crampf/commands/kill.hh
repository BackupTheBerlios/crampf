//
// $Id: kill.hh,v 1.1 2000/03/21 14:29:34 logic Exp $
//

#ifndef KILL
#define KILL KILL

#include "../command.hh"
#include <string>

class Kill : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

