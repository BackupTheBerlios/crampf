//
// $Id: regex.hh,v 1.3 2002/06/01 17:27:39 logic Exp $
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
	RegEx( string re, int flags );
	~RegEx();
	bool match( string s );
    private:
	regex_t preg;	/* compiled regexp */
	int cflags;
};

#endif

