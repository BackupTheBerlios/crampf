//
// $Id: write.hh,v 1.4 2002/06/04 12:04:19 logic Exp $
//

#ifndef WRITE_HH
#define WRITE_HH WRITE_HH

#include "../command.hh"
#include <string>

class Write : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
  private:
    string filename;
    bool commit;
};

#endif

