//
// $Id: track.hh,v 1.7 2002/06/04 12:04:16 logic Exp $
//

#ifndef TRACK_HH
#define TRACK_HH TRACK_HH

#include <string>
#include <stdio.h>

class Track {
  public:
           Track( FILE* fp );
           Track( const string &name );
    string title( void ) const;
    void   title( const string &s );
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

