//
// $Id: debug.hh,v 1.1 2000/09/01 06:43:28 logic Exp $
//

#ifndef __DEBUG_HH
#define __DEBUG_HH __DEBUG_HH

#ifdef DEBUG
#  define printdebug(x...) fprintf(stderr,"DEBUG: "); fprintf(stderr, ## x)
#else
#  define printdebug(x...)
#endif

#endif

