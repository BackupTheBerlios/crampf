//
// $Id: nfilter.hh,v 1.1 2000/03/18 08:14:16 logic Exp $
//

#ifndef nfilter
#define nfilter nfilter

#include "../version_info.hh"
#include <string>
#include "../command.hh"

class NFilter : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

