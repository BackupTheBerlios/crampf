//
// $Id: track.hh,v 1.4 2000/07/16 23:10:19 logic Exp $
//

#ifndef TRACK
#define TRACK TRACK

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

