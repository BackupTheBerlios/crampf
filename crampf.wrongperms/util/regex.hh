//
// $Id: regex.hh,v 1.6 2002/12/28 20:36:57 logic Exp $
//

#ifndef REGEX_HH
#define REGEX_HH REGEX_HH

#include <string>
#include <regex.h>
#define REGEXP_MAXERRLEN	255

/* simple C++-wrapper around GNU regex libc interface 
   ( see regex(3) for details ) */

class RegEx {
    public:
	RegEx( const std::string &re, int cflags );
	~RegEx();
	bool match( const std::string &s, int eflags = 0 ) const;
    private:
	regex_t preg;	/* compiled regexp */
};

#endif

