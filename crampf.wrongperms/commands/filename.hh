//
// $Id: filename.hh,v 1.5 2002/06/04 12:04:18 logic Exp $
//

#ifndef FILENAME_HH
#define FILENAME_HH FILENAME_HH

#include "../command.hh"
#include <string>

class Filename : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

