//
// $Id: track.hh,v 1.5 2002/04/28 00:41:23 logic Exp $
//

#ifndef TRACK
#define TRACK TRACK

#include <string>
#include <stdio.h>

class Track {
  public:
           Track( FILE* fp );
           Track( string name );
    string title( void ) const;
    void   title( string s );
    int    rate( void ) const;
    void   rate( int r );
    string filename( void ) const;
    void   write( FILE* fp );
    bool   operator<(const Track &other) const;
  private:
    string fullname; /* holds path and name */
    string callsign; /* holds short title */
    int    rating;
};

#endif

