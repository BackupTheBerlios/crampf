//
// $Id: define.hh,v 1.1 2000/03/18 17:33:15 logic Exp $
//

#ifndef define
#define define define

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

