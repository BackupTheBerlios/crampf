//
// $Id: jump.hh,v 1.3 2000/03/18 08:14:16 logic Exp $
//

#ifndef jump
#define jump jump

#include "../version_info.hh"
#include <string>
#include "../command.hh"

class Jump : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

