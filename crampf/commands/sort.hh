//
// $Id: sort.hh,v 1.3 2002/06/04 12:04:18 logic Exp $
//

#ifndef SORT_HH
#define SORT_HH SORT_HH

#include "../command.hh"
#include <string>

class Sort : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

