//
// $Id: pfilter.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef PFILTER_HH
#define PFILTER_HH PFILTER_HH

#include <string>
#include "../command.hh"

class PFilter : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

