//
// $Id: loadpfilter.hh,v 1.1 2000/03/18 08:14:16 logic Exp $
//

#ifndef loadpfilter
#define loadpfilter loadpfilter

#include "../version_info.hh"
#include "../command.hh"
#include <string>

class LoadPFilter : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

