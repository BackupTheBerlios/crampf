//
// $Id: nfilter.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef NFILTER_HH
#define NFILTER_HH NFILTER_HH

#include <string>
#include "../command.hh"

class NFilter : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

