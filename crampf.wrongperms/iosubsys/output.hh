/*
 * $Id: output.hh,v 1.1 2003/01/05 12:39:29 logic Exp $
 */

#ifndef __OUTPUT_HH
#  define __OUTPUT_HH __OUTPUT_HH

#include <stdio.h>
#include <queue>
#include <list>
#include <string>

/* generic output backend */
class OutputObject : public std::queue<std::string> {
    public:
	virtual void flush() = 0;
	virtual ~OutputObject() {}
};

/* this class is used by the end user */
class Output : public std::list<OutputObject*> {
    public:
	int printf( char *fmt, ... );
	void flush();
	~Output();
};

extern Output *output;

class StdOutput : public OutputObject {
    public:
	StdOutput();
	void flush();
	~StdOutput();
};

/* further ideas:
class SocketOutput : OutputObject {
};
*/

#endif

