//
// $Id: version.hh,v 1.4 2002/06/01 17:27:37 logic Exp $
//

#ifndef VERSION_HH
#define VERSION_HH VERSION_HH

#include "../command.hh"
#include <string>

class Version : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

