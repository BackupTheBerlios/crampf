#ifndef TCALBACK_HH
#define TCALBACK_HH

#include <assert.h>
#include "value.hh"

//#include <cassert>

///////////////////////////////////////////////////////////////////////////////////

/* Die Basisklasse aller Callbacks mit einem bestimmten Argument- und
   Ergebnistyp. Damit sind die Gemeinsamkeiten ausreichend
   festgelegt. */

template<typename RT, typename AT>
class TCallBackImplBase {
	TCallBackImplBase(const TCallBackImplBase&) {}
  protected:
	TCallBackImplBase() {}
  public:
	virtual ~TCallBackImplBase();

	virtual TCallBackImplBase<RT, AT>*	clone() const=0;
	virtual RT					operator()(AT) const=0;
};

template<typename RT, typename AT>
TCallBackImplBase<RT, AT>::~TCallBackImplBase()
{
}


///////////////////////////////////////////////////////////////////////////////////

/* callback fuer normale Member-functions */

template<typename RT, typename OT, typename AT>
class TCallBackImplMF: public TCallBackImplBase<RT, AT> {
	typedef RT (OT::*Method)(AT);

	OT* const		theObject;
	const Method		theMethod;
  public:
	TCallBackImplMF(const TCallBackImplMF<RT, OT, AT>& o);
	TCallBackImplMF(OT& o, Method m);
	~TCallBackImplMF();

	TCallBackImplBase<RT, AT>*	clone() const;
	RT				operator()(AT) const;
};

template<typename RT, typename OT, typename AT>
TCallBackImplMF<RT, OT, AT>::TCallBackImplMF(const TCallBackImplMF<RT, OT, AT>& o)
:theObject(o.theObject), theMethod(o.theMethod)
{
}

template<typename RT, typename OT, typename AT>
TCallBackImplMF<RT, OT, AT>::TCallBackImplMF(OT& o, Method m)
:theObject(&o), theMethod(m)
{
}

template<typename RT, typename OT, typename AT>
TCallBackImplMF<RT, OT, AT>::~TCallBackImplMF()
{
}

template<typename RT, typename OT, typename AT>
TCallBackImplBase<RT, AT>*
TCallBackImplMF<RT, OT, AT>::clone() const
{
	return new TCallBackImplMF<RT, OT, AT>(*this);
}

template<typename RT, typename OT, typename AT>
RT
TCallBackImplMF<RT, OT, AT>::operator()(AT a) const
{
        assert(theObject!=0 && theMethod!=0);

	return (*theObject.*theMethod)(a);
}


///////////////////////////////////////////////////////////////////////////////////

/* callback fuer const-memberfunctions */

template<typename RT, typename OT, typename AT>
class TCallBackImplCOMF: public TCallBackImplBase<RT, AT> {
	typedef RT (OT::*Method)(AT) const;

	const OT* const	theObject;
	const Method	theMethod;
  public:
	TCallBackImplCOMF(const TCallBackImplCOMF<RT, OT, AT>& o);
	TCallBackImplCOMF(const OT& o, Method m);
	~TCallBackImplCOMF();

	TCallBackImplBase<RT, AT>*	clone() const;
	RT				operator()(AT) const;
};

template<typename RT, typename OT, typename AT>
TCallBackImplCOMF<RT, OT, AT>::TCallBackImplCOMF(const TCallBackImplCOMF<RT, OT, AT>& o)
:theObject(o.theObject), theMethod(o.theMethod)
{
}

template<typename RT, typename OT, typename AT>
TCallBackImplCOMF<RT, OT, AT>::TCallBackImplCOMF(const OT& o, Method m)
:theObject(&o), theMethod(m)
{
}

template<typename RT, typename OT, typename AT>
TCallBackImplCOMF<RT, OT, AT>::~TCallBackImplCOMF()
{
}

template<typename RT, typename OT, typename AT>
TCallBackImplBase<RT, AT>*
TCallBackImplCOMF<RT, OT, AT>::clone() const
{
	return new TCallBackImplCOMF<RT, OT, AT>(*this);
}

template<typename RT, typename OT, typename AT>
RT
TCallBackImplCOMF<RT, OT, AT>::operator()(AT a) const
{
        assert(theObject!=0 && theMethod!=0);

	return (*theObject.*theMethod)(a);
}

///////////////////////////////////////////////////////////////////////////////////

/* callback fuer "normale" Funktionen */

template<typename RT, typename AT>
class TCallBackImplGF: public TCallBackImplBase<RT, AT> {
	typedef RT (*Method)(AT);

	const Method		theMethod;
  public:
	TCallBackImplGF(const TCallBackImplGF<RT, AT>& o);
	TCallBackImplGF(Method m);
	~TCallBackImplGF();

	TCallBackImplBase<RT, AT>*	clone() const;
	RT				operator()(AT) const;
};

template<typename RT, typename AT>
TCallBackImplGF<RT, AT>::TCallBackImplGF(const TCallBackImplGF<RT, AT>& o)
:theMethod(o.theMethod)
{
}

template<typename RT, typename AT>
TCallBackImplGF<RT, AT>::TCallBackImplGF(Method m)
:theMethod(m)
{
}

template<typename RT, typename AT>
TCallBackImplGF<RT, AT>::~TCallBackImplGF()
{
}

template<typename RT, typename AT>
TCallBackImplBase<RT, AT>*
TCallBackImplGF<RT, AT>::clone() const
{
	return new TCallBackImplGF<RT, AT>(*this);
}

template<typename RT, typename AT>
RT
TCallBackImplGF<RT, AT>::operator()(AT a) const
{
        assert(theMethod!=0);

	return (*theMethod)(a);
}
///////////////////////////////////////////////////////////////////////////////////

/* Die Klasse erlaubt die Aufbewahrung der Instanz einer von
   TCallBackImpl abgeleiteten Klasse als *Wert*. Dies geschieht durch
   Verwaltung eines Zeiger auf diese Instanz. Beim Kopieren wird uber
   clone() eine Kopie erzeugt und in der neuen Instanz von TCallBack
   verwaltet. Das ist zwar nicht ganz so nett, wie "smart-pointers",
   aber viel einfacher zu implementieren.

   Vielleicht sollte man da mal ueber die Implementation eines
   templates fuer diese Art von Funktionalitaet nachdenken?

*/


template<typename RT, typename AT>
TCallBackImplBase<RT, AT>*
CloneValue(const TCallBackImplBase<RT, AT>* obj)
{
        return obj->clone();
}

#if 0
template<typename RT, typename AT>
TCallBackImplBase<RT, AT>*
FreeValue(const TCallBackImplBase<RT, AT>* obj)
{
        delete obj;
}
#endif

template<typename RT, typename AT>
class TCallBack : protected Value<TCallBackImplBase<RT, AT> > {
  public:
  TCallBack(const TCallBackImplBase<RT, AT>& cb) : Value<TCallBackImplBase<RT, AT> >(cb) { }
        typedef AT argument_type;
        typedef RT result_type;

        RT	operator()(AT) const;
        RT	call(AT a) const { return (*this)(a); }
};


template<typename RT, typename AT>
RT
TCallBack<RT, AT>::operator()(AT a) const
{
	assert((&(GetValue()) != static_cast<TCallBackImplBase<RT, AT>*>(0)));

	return (GetValue())(a);
}

///////////////////////////////////////////////////////////////////////////////////

/*
  
  Zum Schluss kommt die Schnittstelle zur Instanziierung eines
  CallBack, dies geschieht ueber die Verwendung von Helper-Funktionen,
  die aufgrund des Aufruf-Mechanismus fuer template-Funktionen viel
  bequeumer sind, als die direkte Instanziierung.

*/

template<typename RT, typename OT, typename AT>
TCallBack<RT, AT>
MF_callback(OT& object, RT (OT::*method)(AT))
{
	TCallBackImplMF<RT, OT, AT>	cb(object, method);

	return TCallBack<RT, AT>(cb);
}

template<typename RT, typename OT, typename AT>
TCallBack<RT, AT>
COMF_callback(const OT& object, RT (OT::*method)(AT) const)
{
	TCallBackImplCOMF<RT, OT, AT>	cb(object, method);

	return TCallBack<RT, AT>(cb);
}

template<typename RT, typename AT>
TCallBack<RT, AT>
GF_callback(RT (*method)(AT))
{
	TCallBackImplGF<RT, AT>	cb(method);

	return TCallBack<RT, AT>(cb);
}
// ----
template<typename RT, typename OT, typename AT>
TCallBack<RT, AT>
callback(OT& object, RT (OT::*method)(AT))
{
		return MF_callback(object,method);
}

template<typename RT, typename OT, typename AT>
TCallBack<RT, AT>
callback(const OT& object, RT (OT::*method)(AT) const)
{
	return COMF_callback(object,method);
}

template<typename RT, typename AT>
TCallBack<RT, AT>
callback(RT (*method)(AT))
{
	return GF_callback(method);
}

///////////////////////////////////////////////////////////////////////////////////

#endif
