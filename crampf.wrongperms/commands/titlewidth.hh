//
// $Id: titlewidth.hh,v 1.2 2000/07/16 23:00:57 logic Exp $
//

#ifndef TITLEWIDTH
#define TITLEWIDTH TITLEWIDTH

#include "../command.hh"
#include <string>

class TitleWidth : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

