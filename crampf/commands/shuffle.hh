//
// $Id: shuffle.hh,v 1.3 2000/03/18 08:14:17 logic Exp $
//

#ifndef shuffle
#define shuffle shuffle

#include "../version_info.hh"
#include <string>
#include "../command.hh"

class Shuffle : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};
#endif

