//
// $Id: loadpfilter.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef LOADPFILTER_HH
#define LOADPFILTER_HH LOADPFILTER_HH

#include "../command.hh"
#include <string>

class LoadPFilter : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

