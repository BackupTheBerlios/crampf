//
// $Id: randomorder.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef RANDOMORDER_HH
#define RANDOMORDER_HH RANDOMORDER_HH

#include "../command.hh"
#include <string>

class RandomOrder : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

