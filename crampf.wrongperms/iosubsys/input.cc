#include "input.hh"

Input::Input()
{
}

Input::~Input()
{
      for( iterator it = begin(); it != end(); it++ )
	  delete *it;
}

std::string
Input::read()
{
      std::string res;
      for( iterator it = begin(); it != end(); it++ ){
	  res = (*it)->read();
	  if( res != "" ) /* FIXME this is NOT fair queuing !!! */
	      return res;
      }
      return std::string( "" );
}

