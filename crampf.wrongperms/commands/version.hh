//
// $Id: version.hh,v 1.2 2000/03/18 08:14:17 logic Exp $
//

#ifndef version
#define version version

#include "../version_info.hh"
#include "../command.hh"
#include <string>

class Version : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

