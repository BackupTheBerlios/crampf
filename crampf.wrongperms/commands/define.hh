//
// $Id: define.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
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
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
  protected:
    void showdefine( const string &s ) const;
    void showdefines() const;
    void adddef( string s );
    CommandMap* cmap;
};

#endif

