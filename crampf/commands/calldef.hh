//
// $Id: calldef.hh,v 1.1 2000/03/18 17:33:14 logic Exp $
//

#ifndef calldef
#define calldef calldef

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
