//
// $Id: write.hh,v 1.5 2002/12/24 19:51:51 logic Exp $
//

#ifndef WRITE_HH
#define WRITE_HH WRITE_HH

#include "../command.hh"
#include <string>

class Write : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
  private:
    std::string filename;
    bool commit;
};

#endif

