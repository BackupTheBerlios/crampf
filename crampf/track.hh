//
// $Id: track.hh,v 1.9 2002/12/24 19:51:48 logic Exp $
//

#ifndef TRACK_HH
#define TRACK_HH TRACK_HH

#include <string>
#include <stdio.h>

class Track {
  public:
           Track( FILE* fp );
           Track( const std::string &name );
    std::string title( void ) const;
    void   title( const std::string &s );
    int    rate( void ) const;
    void   rate( int r );
    std::string filename( void ) const;
    void   write( FILE* fp );
    bool   operator<(const Track &other) const;
    bool   operator==(const Track &other ) const;
    bool   operator!=(const Track &other ) const;
  private:
    std::string fullname; /* holds path and name */
    std::string callsign; /* holds short title */
    int    rating;
};

#endif

