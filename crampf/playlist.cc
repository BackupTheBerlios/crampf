/*
 * Playlist Class -- contains the playlist, handels filters
 */

#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include <unistd.h>
#include "playlist.hh"
#include "config.hh"
#include "util/regex.hh"

extern struct options* opts;

Playlist::Playlist()
{
  current=0;
}

void 
Playlist::addPath( const string &path )
{
  struct stat buf;
  stat((const char*)path.c_str(),&buf);
  if (!(S_ISDIR(buf.st_mode))) {
    /* only a single file to add */
    if (S_ISREG(buf.st_mode)) addTrack("",path);
    return;
  }
  FILE* fp;
  string findcmd = "find \"" + path + "\" -iname \"*.mp3\" -type f -follow";
  fp = popen((const char*)findcmd.c_str(),"r");
  if (fp==NULL) {
    perror((const char*)path.c_str());
    return;
  }
  char cbuf[MAXFILENAMELENGTH];
  while (fgets(cbuf,MAXFILENAMELENGTH,fp)) {
    cbuf[strlen(cbuf)-1]='\0'; /* strip ending '\n' */
    addTrack(path,&cbuf[path.size()]);
  }
  pclose(fp);
}

void 
Playlist::addPath( const vector<string> &path )
{
  for (vector<string>::const_iterator it = path.begin();
      it != path.end(); it++)
    addPath(*it);
}

void
Playlist::savePlaylist( string filename )
{
  if (filename[0]=='~') { // replace ~ with users home
    filename.erase(filename.begin());
    filename = getenv("HOME") + filename;
  }
  FILE* fp=fopen(filename.c_str(),"w");
  if (fp==NULL) {
    perror("save Playlist");
    return;
  }
  for (Playlist::iterator it = begin();
      it != end(); it++)
    it->write(fp);
  fclose(fp);
}

void
Playlist::addPlaylist( string filename )
{
  if (filename[0]=='~') { // replace ~ with users home
    filename.erase(filename.begin());
    filename = getenv("HOME") + filename;
  }
  FILE* fp=fopen(filename.c_str(),"r");
  if (fp==NULL) {
    perror("read Playlist");
    return;
  }
  try {
    while (1)
      addTrack(fp);
  } catch (string error) {
  }
  fclose(fp);
}

void
Playlist::addPlaylist( const vector<string> &filenames )
{
  for (vector<string>::const_iterator it = filenames.begin();
      it != filenames.end(); it++)
    addPlaylist(*it);
}

void 
Playlist::positiveFilter( const string &flt )
{
      int flags = REG_NOSUB, c=current, i=0;
      if (!opts->casesensivity)
	  flags = flags | REG_ICASE;
      if (opts->regexp==2)
	  flags = flags | REG_EXTENDED;
      RegEx re = RegEx( flt, flags );
      for (Playlist::iterator it = begin();
	      it != end(); it++,i++) 
	  if ( !re.match( it->title().c_str() ) ) {
	      if( i < c )
		  current--;
	      erase(it--);
	  }
}

void 
Playlist::positiveFilter( const vector<string> &flt )
{
  for (vector<string>::const_iterator it = flt.begin();
      it != flt.end(); it++)
    positiveFilter(*it);
}

void 
Playlist::negativeFilter( const string &flt )
{
      int flags = REG_NOSUB, c=current, i=0;
      if (!opts->casesensivity)
	  flags = flags | REG_ICASE;
      if (opts->regexp==2)
	  flags = flags | REG_EXTENDED;
      RegEx re = RegEx( flt, flags );
      for (Playlist::iterator it = begin();
	      it != end(); it++,i++) 
	  if ( re.match( it->title().c_str() ) ) {
	      if( i < c )
		  current--;
	      erase(it--);
	  }
}

void 
Playlist::negativeFilter( const vector<string> &flt )
{
  for (vector<string>::const_iterator it = flt.begin();
      it != flt.end(); it++) {
    negativeFilter(*it);
  }
}

vector<string>
Playlist::loadFilterFile( const string &filename )
{
  vector<string> flt;
  FILE* fp = fopen((const char*)filename.c_str(),"r");
  if (fp==NULL) {
    perror((const char*)filename.c_str());
    throw string("cannot open filterfile");
  }
  char line[FILELINEWIDTH];
  while (fgets(line,FILELINEWIDTH,fp)) {
    if (line[0]!='#' && line[0]!='\n') {
      line[strlen(line)-1]='\0'; /* remove '\n' */
      flt.push_back(line);
    }
  }
  fclose(fp);
  return flt;
}

void
Playlist::loadNegativeFilter( const string &filename )
{
  negativeFilter( loadFilterFile( filename ) );
}

void
Playlist::loadPositiveFilter( const string &filename )
{
  positiveFilter( loadFilterFile( filename ) );
}

void
Playlist::loadNegativeFilter( const vector<string> &filenames )
{
  for( vector<string>::const_iterator it = filenames.begin();
	  it != filenames.end(); it++ )
      negativeFilter( loadFilterFile( *it ) );
}

void
Playlist::loadPositiveFilter( const vector<string> &filenames )
{
  for( vector<string>::const_iterator it = filenames.begin();
	  it != filenames.end(); it++ )
      positiveFilter( loadFilterFile( *it  ) );
}

void
Playlist::shuffle()
{
  srand(time(NULL));
  for (int i=0; i<size(); i++) {
    Track h = (*this)[i];
    int x = rand()%size();
    (*this)[i] = (*this)[x];
    (*this)[x] = h;
  }
}

Track 
Playlist::operator++()
{
  /* FIXME ++command obsolete? */
  jump(pos()+1);
  return (*this)[current];
}

Track 
Playlist::operator--()
{
  /* FIXME --command obsolete? */
  jump(pos()+1);
  return (*this)[current];
}
    
Track 
Playlist::operator*() const
{
  return (*this)[current];
}

int 
Playlist::pos() const
{
  return current;
}

void 
Playlist::jump(int newpos)
{
  if (size() == 0) 
      throw string("empty playlist");
  while (newpos<0) {
    opts->loop--;
    newpos+=size();
  }
  if (newpos>size()-1) {
    if (opts->loop>0)
      opts->loop-=(int)ceil((double)newpos/(double)size());
    if (opts->loop<=0)
      throw string("end of playlist");
    newpos%=(size());
  }
  current=newpos;
}

void 
Playlist::addTrack( const string &path, string filename )
{
  push_back(Track(path+filename));
  if (opts->generateTitles) {
    filename.erase(filename.end()-4,filename.end());
    (*this)[size()-1].title(filename);
  }
}

void 
Playlist::addTrack( FILE* fp )
{
  push_back(Track(fp));
}

