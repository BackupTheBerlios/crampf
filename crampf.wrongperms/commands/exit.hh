//
// $Id: exit.hh,v 1.2 2002/06/01 17:27:37 logic Exp $
//

#ifndef EXIT_HH
#define EXIT_HH EXIT_HH

#include "../command.hh"
#include <string>

class Exit: public Command {
    public:
	void doit( string s );
	void help( string s );
	void description();
};

#endif

