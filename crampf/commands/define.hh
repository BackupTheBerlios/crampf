//
// $Id: define.hh,v 1.2 2000/07/16 23:00:56 logic Exp $
//

#ifndef DEFINE
#define DEFINE DEFINE

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

