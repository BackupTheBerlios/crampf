//
// $Id: listtracks.hh,v 1.4 2002/12/24 19:51:50 logic Exp $
//

#ifndef LISTTRACKS_HH
#define LISTTRACKS_HH LISTTRACKS_HH

#include <string>
#include "../command.hh"

class ListTracks : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

