//
// $Id: track.hh,v 1.3 2000/03/19 12:44:20 logic Exp $
//

#ifndef track
#define track

#include "version_info.hh"
#include <string>
#include <stdio.h>

class Track {
  public:
           Track( FILE* fp );
           Track( string name );
    string title( void );
    void   title( string s );
    int    rate( void );
    void   rate( int r );
    string filename( void );
    void   write( FILE* fp );
  private:
    string fullname; /* holds path and name */
    string callsign; /* holds short title */
    int    rating;
};

#endif

