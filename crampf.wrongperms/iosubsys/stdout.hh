/*
 * $Id: stdout.hh,v 1.1 2003/01/11 20:33:40 logic Exp $
 */

#ifndef __STDOUT_HH
#  define __STDOUT_HH __STDOUT_HH

#include "output.hh"

class StdOutput : public OutputObject {
    public:
	StdOutput();
	void flush();
	~StdOutput();
	void configure( const std::string &s );
	void help( const std::string &s ) const;
	void description() const;
};

#endif

