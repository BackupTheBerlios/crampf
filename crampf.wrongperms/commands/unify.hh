//
// $Id: unify.hh,v 1.4 2002/06/04 12:04:19 logic Exp $
//

#ifndef UNIFY_HH
#define UNIFY_HH UNIFY_HH

#include "../command.hh"
#include <string>

class Unify : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

