//
// $Id: calldef.hh,v 1.6 2003/01/11 16:01:38 logic Exp $
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
    void execute( const std::string &macro, const std::string &args );
    CommandMap* cmap;
};

#endif
