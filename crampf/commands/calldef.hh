//
// $Id: calldef.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
//

#ifndef CALLDEF_HH
#define CALLDEF_HH CALLDEF_HH

#include "../command.hh"
#include "../commandmap.hh"
#include <string>

class CallDef : public Command {
  public:
    CallDef( CommandMap* c );
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
  private:
    void execute( const std::string &s );
    CommandMap* cmap;
};

#endif
