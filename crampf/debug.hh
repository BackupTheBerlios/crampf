//
// $Id: debug.hh,v 1.4 2002/12/28 23:11:51 logic Exp $
//

#ifndef __DEBUG_HH
#define __DEBUG_HH __DEBUG_HH

#include <stdio.h>
#include "config.h"

#ifdef DEBUG
#  define printdebug(fmt,args...) fprintf(stderr,"DEBUG:%-16s[%3d] "##fmt,__FILE__,__LINE__,args)
#else
#  define printdebug(fmt,args...)
#endif

#endif

