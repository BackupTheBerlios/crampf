//
// $Id: pfilter.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
//

#ifndef PFILTER_HH
#define PFILTER_HH PFILTER_HH

#include <string>
#include "../command.hh"

class PFilter : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

