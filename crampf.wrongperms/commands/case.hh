//
// $Id: case.hh,v 1.3 2002/06/04 12:04:18 logic Exp $
//

#ifndef CASE_HH
#define CASE_HH CASE_HH

#include "../command.hh"
#include <string>

class Case: public Command {
    public:
	void doit( const string &s );
	void help( const string &s ) const;
	void description() const;
};

#endif

