//
// $Id: titlewidth.hh,v 1.4 2002/06/04 12:04:19 logic Exp $
//

#ifndef TITLEWIDTH_HH
#define TITLEWIDTH_HH TITLEWIDTH_HH

#include "../command.hh"
#include <string>

class TitleWidth : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

