//
// $Id: addpath.hh,v 1.3 2000/03/18 08:14:16 logic Exp $
//

#ifndef addpath
#define addpath addpath

#include "../version_info.hh"
#include <string>
#include "../command.hh"

class AddPath : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

