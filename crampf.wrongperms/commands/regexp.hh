//
// $Id: regexp.hh,v 1.4 2002/12/24 19:51:50 logic Exp $
//

#ifndef REGEXP_HH
#define REGEXP_HH REGEXP_HH

#include "../command.hh"
#include <string>

class RegExp: public Command {
    public:
	void doit( const std::string &s );
	void help( const std::string &s ) const;
	void description() const;
};

#endif

