//
// $Id: nfilter.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
//

#ifndef NFILTER_HH
#define NFILTER_HH NFILTER_HH

#include <string>
#include "../command.hh"

class NFilter : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

