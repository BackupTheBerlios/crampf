//
// $Id: titlewidth.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef TITLEWIDTH_HH
#define TITLEWIDTH_HH TITLEWIDTH_HH

#include "../command.hh"
#include <string>

class TitleWidth : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

