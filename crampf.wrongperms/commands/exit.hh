//
// $Id: exit.hh,v 1.1 2000/07/15 23:00:52 logic Exp $
//

#ifndef EXIT
#define EXIT EXIT

#include "../command.hh"
#include <string>

class Exit: public Command {
    public:
	void doit( string s );
	void help( string s );
	void description();
};

#endif

