//
// $Id: case.hh,v 1.2 2002/06/01 17:27:37 logic Exp $
//

#ifndef CASE_HH
#define CASE_HH CASE_HH

#include "../command.hh"
#include <string>

class Case: public Command {
    public:
	void doit( string s );
	void help( string s );
	void description();
};

#endif

