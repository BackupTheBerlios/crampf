//
// $Id: calldef.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef CALLDEF_HH
#define CALLDEF_HH CALLDEF_HH

#include "../command.hh"
#include "../commandmap.hh"
#include <string>

class CallDef : public Command {
  public:
    CallDef( CommandMap* c );
    void doit( string s );
    void help( string s );
    void description();
  private:
    void execute( string s );
    CommandMap* cmap;
};

#endif
