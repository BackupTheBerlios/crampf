//
// $Id: version.hh,v 1.6 2002/12/24 19:51:50 logic Exp $
//

#ifndef VERSION_HH
#define VERSION_HH VERSION_HH

#include "../command.hh"
#include <string>

class Version : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

