/*
 * Track Class extends trackinformation to more than just a string
 */

#include "version_info.hh"
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
  sscanf(line,"\"%[^\"]\";\"%[^\"]\";\"%d\"",f,c,&rating);
  fullname=f;
  callsign=c;
}

Track::Track( string name )
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
