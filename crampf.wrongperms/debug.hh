//
// $Id: debug.hh,v 1.3 2002/07/02 15:58:00 logic Exp $
//

#ifndef __DEBUG_HH
#define __DEBUG_HH __DEBUG_HH

#include "config.h"

#ifdef DEBUG
#  define printdebug(fmt,args...) fprintf(stderr,"DEBUG:%-16s[%3d] "##fmt,__FILE__,__LINE__,args)
#else
#  define printdebug(fmt,args...)
#endif

#endif

