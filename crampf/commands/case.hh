//
// $Id: case.hh,v 1.4 2002/12/24 19:51:50 logic Exp $
//

#ifndef CASE_HH
#define CASE_HH CASE_HH

#include "../command.hh"
#include <string>

class Case: public Command {
    public:
	void doit( const std::string &s );
	void help( const std::string &s ) const;
	void description() const;
};

#endif

