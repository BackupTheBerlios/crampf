//
// $Id: define.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef DEFINE_HH
#define DEFINE_HH DEFINE_HH

#include <string>
#include <vector>
#include <map>
#include "../command.hh"
#include "../commandmap.hh"

class Define : public Command {
  public:
    Define( CommandMap* c );
    void doit( string s );
    void help( string s );
    void description();
  protected:
    void showdefine( string s );
    void showdefines();
    void adddef( string s );
    CommandMap* cmap;
};

#endif

