//
// $Id: source.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
//

#ifndef SOURCE_HH
#define SOURCE_HH SOURCE_HH

#include "../command.hh"
#include "../commandmap.hh"
#include <string>

class Source : public Command {
  public:
    Source( CommandMap* c );
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
  private:
    CommandMap* cmap;
};

#endif

