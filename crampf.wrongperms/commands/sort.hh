//
// $Id: sort.hh,v 1.4 2002/12/24 19:51:50 logic Exp $
//

#ifndef SORT_HH
#define SORT_HH SORT_HH

#include "../command.hh"
#include <string>

class Sort : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

