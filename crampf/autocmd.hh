//
// $Id: autocmd.hh,v 1.6 2002/12/24 19:51:48 logic Exp $
//

#ifndef __AUTOCMD_HH
#  define __AUTOCMD_HH __AUTOCMD_HH

#include <string>
#include <list>
#include <map>
#include "cb/tcalback.hh"
#include "debug.hh"

typedef TCallBack<bool,const std::string&> AutoCB;

class AutocmdHandler {
    public:
	std::string name, description;
	std::list<AutoCB> cbs;
	AutocmdHandler(){} // dummy constructor
	AutocmdHandler( const std::string &event, const std::string &descr )
	    : name(event), description(descr) {}
	void registerCB( const AutoCB &cb )
	  { printdebug( "registered callback on event '%s'\n", name.c_str() );
	    cbs.push_back( cb ); }
	const std::string& getDescription( const std::string &event ) const
	  { return description; }
	void trigger() const
	  {
	    printdebug("AutocmdHandler::trigger - %s\n", name.c_str() );
	    for( std::list<AutoCB>::const_iterator it = cbs.begin();
		  it != cbs.end(); it++ ){
		printdebug( "delivering event... %s\n", name.c_str() );
	      (*it)( name );
	    }
	  }
};

class AutocmdMap : public std::map<std::string,AutocmdHandler> {
    public:
	//AutocmdMap(){}
	void newEvent( const std::string &event, const std::string &description )
	  { printdebug( "created new event '%s'\n", event.c_str() );
	    (*this)[event] = AutocmdHandler( event, description ); }
	//~AutocmdMap();

};

extern AutocmdMap autocmdmap;

#endif

