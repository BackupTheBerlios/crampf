//
// $Id: filename.hh,v 1.6 2002/12/24 19:51:50 logic Exp $
//

#ifndef FILENAME_HH
#define FILENAME_HH FILENAME_HH

#include "../command.hh"
#include <string>

class Filename : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

