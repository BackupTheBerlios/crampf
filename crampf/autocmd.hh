//
// $Id: autocmd.hh,v 1.4 2002/06/04 12:04:15 logic Exp $
//

#ifndef __AUTOCMD_HH
#  define __AUTOCMD_HH __AUTOCMD_HH

#include <string>
#include <list>
#include <map>
#include "cb/tcalback.hh"
#include "debug.hh"

typedef TCallBack<bool,const string&> AutoCB;

class AutocmdHandler {
    public:
	string name, description;
	list<AutoCB> cbs;
	AutocmdHandler(){} // dummy constructor
	AutocmdHandler( const string &event, const string &descr )
	    : name(event), description(descr) {}
	void registerCB( const AutoCB &cb )
	  { printdebug( "registered callback on event '%s'\n", name.c_str() );
	    cbs.push_back( cb ); }
	const string& getDescription( const string &event ) const
	  { return description; }
	void trigger() const
	  {
	    printdebug("AutocmdHandler::trigger\n");
	    for( list<AutoCB>::const_iterator it = cbs.begin();
		  it != cbs.end(); it++ ){
		printdebug( "delivering event...\n" );
	      (*it)( name );
	    }
	  }
};

class AutocmdMap : public map<string,AutocmdHandler> {
    public:
	//AutocmdMap(){}
	void newEvent( const string &event, const string &description )
	  { printdebug( "created new event '%s'\n", event.c_str() );
	    (*this)[event] = AutocmdHandler( event, description ); }
	//~AutocmdMap();

};

extern AutocmdMap autocmdmap;

#endif

