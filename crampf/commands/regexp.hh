//
// $Id: regexp.hh,v 1.2 2002/06/01 17:27:37 logic Exp $
//

#ifndef REGEXP_HH
#define REGEXP_HH REGEXP_HH

#include "../command.hh"
#include <string>

class RegExp: public Command {
    public:
	void doit( string s );
	void help( string s );
	void description();
};

#endif

