//
// $Id: shuffle.hh,v 1.2 2000/03/18 04:38:11 logic Exp $
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
};
#endif

