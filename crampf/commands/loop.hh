//
// $Id: loop.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef LOOP_HH
#define LOOP_HH LOOP_HH

#include "../command.hh"
#include <string>

class Loop : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

