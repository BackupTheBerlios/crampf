//
// $Id: case.hh,v 1.1 2000/07/03 02:02:40 logic Exp $
//

#ifndef CASE
#define CASE CASE

#include "../command.hh"
#include <string>

class Case: public Command {
    public:
	void doit( string s );
	void help( string s );
	void description();
};

#endif

