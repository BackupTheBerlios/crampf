/*
 * Track Class extends trackinformation to more than just a string
 */

#include <string>
#include <stdio.h>
#include "track.hh"

Track::Track( FILE* fp )
{
#define MAXLINEWIDTH 8192
  char line[MAXLINEWIDTH];
  if (fgets(line,MAXLINEWIDTH,fp)==NULL)
    throw string("error reading playlist");
  char f[MAXLINEWIDTH];
  char c[MAXLINEWIDTH];
  if (sscanf(line,"\"%[^\"]\";\"%[^\"]\";\"%d\"",f,c,&rating) == 0) {
      /* playlist has bad format, try to load it in the `old' way */
      string trackname = string(line);
      /* strip '\n' */
      trackname.erase(trackname.length()-1,trackname.length());
      fullname=trackname;
      callsign=trackname;
      rating = 0;
  } else {
      fullname=f;
      callsign=c;
  }
}

Track::Track( const string &name )
{
  fullname = name;
  rating = 0;
}

void
Track::write( FILE* fp )
{
  fprintf(fp,"\"%s\";\"%s\";\"%d\"\n",fullname.c_str(),callsign.c_str(),rating);
}

string 
Track::title( void ) const
{
  if (!callsign.empty())
    return callsign;
  else
    return fullname;
}

void   
Track::title( const string &s )
{
  callsign = s;
}

int    
Track::rate( void ) const
{
  return rating;
}

void   
Track::rate( int r )
{
  rating = r;
}

string 
Track::filename( void ) const
{
  return fullname;
}

bool
Track::operator<(const Track &other) const
{
      return filename() < other.filename();
}

bool
Track::operator==( const Track &other ) const
{
      return filename() == other.filename();
}
