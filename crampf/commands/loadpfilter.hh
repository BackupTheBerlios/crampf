//
// $Id: loadpfilter.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
//

#ifndef LOADPFILTER_HH
#define LOADPFILTER_HH LOADPFILTER_HH

#include "../command.hh"
#include <string>

class LoadPFilter : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

