//
// $Id: loadnfilter.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef LOADNFILTER_HH
#define LOADNFILTER_HH LOADNFILTER_HH

#include "../command.hh"
#include <string>

class LoadNFilter : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

