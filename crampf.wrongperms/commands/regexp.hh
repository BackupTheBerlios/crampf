//
// $Id: regexp.hh,v 1.1 2000/07/03 02:02:40 logic Exp $
//

#ifndef REGEXP
#define REGEXP REGEXP

#include "../command.hh"
#include <string>

class RegExp: public Command {
    public:
	void doit( string s );
	void help( string s );
	void description();
};

#endif

