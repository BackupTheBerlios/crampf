//
// $Id: source.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef SOURCE_HH
#define SOURCE_HH SOURCE_HH

#include "../command.hh"
#include "../commandmap.hh"
#include <string>

class Source : public Command {
  public:
    Source( CommandMap* c );
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
  private:
    CommandMap* cmap;
};

#endif

