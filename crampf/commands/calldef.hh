//
// $Id: calldef.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef CALLDEF_HH
#define CALLDEF_HH CALLDEF_HH

#include "../command.hh"
#include "../commandmap.hh"
#include <string>

class CallDef : public Command {
  public:
    CallDef( CommandMap* c );
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
  private:
    void execute( const string &s );
    CommandMap* cmap;
};

#endif
