//
// $Id: listtracks.hh,v 1.3 2002/06/04 12:04:18 logic Exp $
//

#ifndef LISTTRACKS_HH
#define LISTTRACKS_HH LISTTRACKS_HH

#include <string>
#include "../command.hh"

class ListTracks : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

