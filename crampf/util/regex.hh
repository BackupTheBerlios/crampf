//
// $Id: regex.hh,v 1.1 2000/07/08 17:57:53 logic Exp $
//

#ifndef regex
#define regex regex

#include "../version_info.hh"
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

