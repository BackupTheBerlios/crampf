//
// $Id: exit.hh,v 1.3 2002/06/04 12:04:18 logic Exp $
//

#ifndef EXIT_HH
#define EXIT_HH EXIT_HH

#include "../command.hh"
#include <string>

class Exit: public Command {
    public:
	void doit( const string &s );
	void help( const string &s ) const;
	void description() const;
};

#endif

