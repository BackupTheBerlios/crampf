//
// $Id: shuffle.hh,v 1.6 2002/06/04 12:04:18 logic Exp $
//

#ifndef SHUFFLE_HH
#define SHUFFLE_HH SHUFFLE_HH

#include <string>
#include "../command.hh"

class Shuffle : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};
#endif

