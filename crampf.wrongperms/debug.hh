//
// $Id: debug.hh,v 1.2 2002/07/01 20:03:30 logic Exp $
//

#ifndef __DEBUG_HH
#define __DEBUG_HH __DEBUG_HH

#include "config.h"

#ifdef DEBUG
#  define printdebug(x...) fprintf(stderr,"DEBUG: "); fprintf(stderr, ## x)
#else
#  define printdebug(x...)
#endif

#endif

