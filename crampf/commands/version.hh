//
// $Id: version.hh,v 1.5 2002/06/04 12:04:19 logic Exp $
//

#ifndef VERSION_HH
#define VERSION_HH VERSION_HH

#include "../command.hh"
#include <string>

class Version : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

