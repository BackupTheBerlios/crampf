//
// $Id: calldef.hh,v 1.2 2000/07/16 23:00:56 logic Exp $
//

#ifndef CALLDEF
#define CALLDEF CALLDEF

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
