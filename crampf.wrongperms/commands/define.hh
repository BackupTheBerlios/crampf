//
// $Id: define.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
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
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
  protected:
    void showdefine( const std::string &s ) const;
    void showdefines() const;
    void adddef( std::string s );
    CommandMap* cmap;
};

#endif

