//
// $Id: track.hh,v 1.1 2000/03/10 04:02:30 logic Exp $
//

#ifndef track
#define track

#include <string>

class Track {
  public:
           Track ( string name );
    string title( void );
    void   title( string s );
    int    rate( void );
    void   rate( int r );
    string filename( void );
  private:
    string fullname; /* holds path and name */
    string callsign; /* holds short title */
    int    rating;
};

#endif

