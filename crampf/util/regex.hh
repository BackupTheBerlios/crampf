//
// $Id: regex.hh,v 1.2 2000/07/16 23:01:43 logic Exp $
//

#ifndef REGEX
#define REGEX REGEX

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

