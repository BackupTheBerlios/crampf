//
// $Id: track.hh,v 1.2 2000/03/18 04:38:09 logic Exp $
//

#ifndef track
#define track

#include "version_info.hh"
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

