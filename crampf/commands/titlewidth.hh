//
// $Id: titlewidth.hh,v 1.1 2000/03/18 13:48:07 logic Exp $
//

#ifndef TITLEWIDTH
#define TITLEWIDTH TITLEWIDTH

#include "../command.hh"
#include "../version_info.hh"
#include <string>

class TitleWidth : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

