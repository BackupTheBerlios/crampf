/*
 * Track Class extends trackinformation to more than just a string
 */

#include "version_info.hh"
#include <string>
#include "track.hh"

Track::Track( string name )
{
  fullname = name;
}

string 
Track::title( void )
{
  if (!callsign.empty())
    return callsign;
  else
    return fullname;
}

void   
Track::title( string s )
{
  callsign = s;
}

int    
Track::rate( void )
{
  return rating;
}

void   
Track::rate( int r )
{
  rating = r;
}

string 
Track::filename( void )
{
  return fullname;
}
