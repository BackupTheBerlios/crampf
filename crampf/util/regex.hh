//
// $Id: regex.hh,v 1.4 2002/06/04 12:04:21 logic Exp $
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
	RegEx( const string &re, int flags );
	~RegEx();
	bool match( const string &s ) const;
    private:
	regex_t preg;	/* compiled regexp */
	int cflags;
};

#endif

