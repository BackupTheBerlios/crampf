//
// $Id: addpath.hh,v 1.6 2002/06/04 12:04:18 logic Exp $
//

#ifndef ADDPATH_HH
#define ADDPATH_HH ADDPATH_HH

#include <string>
#include "../command.hh"

class AddPath : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

