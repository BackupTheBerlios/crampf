//
// $Id: regexp.hh,v 1.3 2002/06/04 12:04:18 logic Exp $
//

#ifndef REGEXP_HH
#define REGEXP_HH REGEXP_HH

#include "../command.hh"
#include <string>

class RegExp: public Command {
    public:
	void doit( const string &s );
	void help( const string &s ) const;
	void description() const;
};

#endif

