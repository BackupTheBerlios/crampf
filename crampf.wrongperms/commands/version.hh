//
// $Id: version.hh,v 1.3 2000/07/16 23:00:57 logic Exp $
//

#ifndef VERSION
#define VERSION VERSION

#include "../command.hh"
#include <string>

class Version : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

