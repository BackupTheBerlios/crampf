#ifndef _Value_H_
#define _Value_H_

/*****************************************************************
 *
 *   FILE:
 *	Value.h
 *
 *   DESCRIPTION:
 *	Template-Klasse mit Value-semantik.
 *	Nach einer Idee von jk
 *
 *	$Author: logic $   $Revision: 1.1 $
 *	$Date: 2002/04/28 00:01:22 $
 *
 *	$Log: value.hh,v $
 *	Revision 1.1  2002/04/28 00:01:22  logic
 *	Added new autocommand feature.
 *	First Autocommand hook implemented: 'next' is called after external player terminates
 *
 *	Revision 1.1  2000/03/30 13:01:06  dku
 *	added tcallback
 *	
 *	Revision 1.2  1999/08/09 08:53:30  dku
 *	Visual C++ porting issues
 *	
 *	Revision 1.1  1999/04/09 16:10:38  dku
 *	Neu: Mbus-Dispatcher
 *
 *	Revision 1.1.1.1  1991/11/29 16:01:03  holly
 *	- Initial check-in from original non-cvs dir on Random
 *	
 *
 *****************************************************************/


#ifndef MSVC // has problems with explicit specialization
template<class T>
T*
CloneValue(const T* obj)
{
	return new T(*obj);
}
#endif

template<class T>
void
FreeValue(T* val)
{
  delete val;
}

/* Hier sollten jetzt passende CloneValue()s und FreeValue()s
   z.B. fuer STL-Container (anlegen eines neuen selben Containers und
  fÅ¸llen per CloneValue auf dem Basisobjekt).  */



template<class T>
class Value {
  T*	theValue;
public:
  Value() : theValue(NULL) { }
  Value(const T& obj) : theValue(CloneValue(&obj)) { }
  Value(const Value& other) : theValue(static_cast<T*>(0)) { *this = other; }
  ~Value() { FreeValue(theValue); }
        Value& operator= (const Value& other) 
    {
      if (this != &other) {
	if (theValue) {
	  FreeValue(theValue);
	}
	if (other.theValue) {
	  theValue = CloneValue(other.theValue);
	} else {
	  theValue = static_cast<T*>(0);
	}
      }
      return *this;
    }
  
  T&	GetValue() const { return *theValue; }
};


#endif

