//
// One class for each command. doit method called by commandmap
//

#ifndef HELP_HH
#define HELP_HH HELP_HH

#include <string>
#include "../command.hh"
#include "../commandmap.hh"

class Help : public Command {
  public:
    Help( CommandMap* c);
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
  private:
    CommandMap* cmap;
};

#endif
