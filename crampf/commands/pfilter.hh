//
// $Id: pfilter.hh,v 1.1 2000/03/18 08:14:16 logic Exp $
//

#ifndef pfilter
#define pfilter pfilter

#include "../version_info.hh"
#include <string>
#include "../command.hh"

class PFilter : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

