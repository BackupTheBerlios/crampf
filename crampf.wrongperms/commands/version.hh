//
// $Id: version.hh,v 1.1 2000/03/18 04:38:11 logic Exp $
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
};

#endif

