//
// $Id: randomorder.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
//

#ifndef RANDOMORDER_HH
#define RANDOMORDER_HH RANDOMORDER_HH

#include "../command.hh"
#include <string>

class RandomOrder : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

