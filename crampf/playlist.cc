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
#include "options.hh"
#include "util/regex.hh"

extern struct options* opts;

Playlist::Playlist()
{
  current=0;
}

void 
Playlist::addPath( const std::string &path )
{
  struct stat buf;
  stat((const char*)path.c_str(),&buf);
  if (!(S_ISDIR(buf.st_mode))) {
    /* only a single file to add */
    if (S_ISREG(buf.st_mode)) addTrack("",path);
    return;
  }
  //std::string findcmd = "find \"" + path + "\" -iname \"*.mp3\" -type f -follow";
  std::string findcmd = "find \"" + path + "\" -type f -follow";
  FILE *fp = popen((const char*)findcmd.c_str(),"r");
  if (fp==NULL) {
    perror((const char*)path.c_str());
    return;
  }
  try {
    char cbuf[MAXFILENAMELENGTH];
    while (fgets(cbuf,MAXFILENAMELENGTH,fp)) {
      cbuf[strlen(cbuf)-1]='\0'; /* strip ending '\n' */
      addTrack(path,&cbuf[path.size()]);
    }
  } catch( std::string error ){
    printf( "EXCEPTION: caught '%s'\n", error.c_str() );
  } catch(...){
    printf( "EXCEPTION: caught something\n" );
  }
  if( fp )
    pclose(fp);
}

void 
Playlist::addPath( const std::vector<std::string> &path )
{
  for (std::vector<std::string>::const_iterator it = path.begin();
      it != path.end(); it++)
    addPath(*it);
}

void
Playlist::savePlaylist( std::string filename )
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
Playlist::addPlaylist( std::string filename )
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
  } catch (std::string error) {
  }
  fclose(fp);
}

void
Playlist::addPlaylist( const std::vector<std::string> &filenames )
{
  for (std::vector<std::string>::const_iterator it = filenames.begin();
      it != filenames.end(); it++)
    addPlaylist(*it);
}

void 
Playlist::positiveFilter( const std::string &flt )
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
Playlist::positiveFilter( const std::vector<std::string> &flt )
{
  for (std::vector<std::string>::const_iterator it = flt.begin();
      it != flt.end(); it++)
    positiveFilter(*it);
}

void 
Playlist::negativeFilter( const std::string &flt )
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
Playlist::negativeFilter( const std::vector<std::string> &flt )
{
  for (std::vector<std::string>::const_iterator it = flt.begin();
      it != flt.end(); it++) {
    negativeFilter(*it);
  }
}

std::vector<std::string>
Playlist::loadFilterFile( const std::string &filename )
{
  std::vector<std::string> flt;
  FILE* fp = fopen((const char*)filename.c_str(),"r");
  if (fp==NULL) {
    perror((const char*)filename.c_str());
    throw std::string("cannot open filterfile");
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
Playlist::loadNegativeFilter( const std::string &filename )
{
  negativeFilter( loadFilterFile( filename ) );
}

void
Playlist::loadPositiveFilter( const std::string &filename )
{
  positiveFilter( loadFilterFile( filename ) );
}

void
Playlist::loadNegativeFilter( const std::vector<std::string> &filenames )
{
  for( std::vector<std::string>::const_iterator it = filenames.begin();
	  it != filenames.end(); it++ )
      negativeFilter( loadFilterFile( *it ) );
}

void
Playlist::loadPositiveFilter( const std::vector<std::string> &filenames )
{
  for( std::vector<std::string>::const_iterator it = filenames.begin();
	  it != filenames.end(); it++ )
      positiveFilter( loadFilterFile( *it  ) );
}

void
Playlist::shuffle()
{
  srand(time(NULL));
  for (unsigned int i=0; i<size(); i++) {
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

unsigned int 
Playlist::pos() const
{
  return current;
}

Playlist::const_iterator
Playlist::ConstIterator( int pos ) const
{
      if( pos == -1 )
	  pos = current;
      const_iterator it = begin();
      for( int i=0; i < pos; i++ )
	  it++;
      return it;
}

Playlist::iterator
Playlist::Iterator( int pos )
{
      if( pos == -1 )
	  pos = current;
      iterator it = begin();
      for( int i=0; i < pos; i++ )
	  it++;
      return it;
}

void 
Playlist::jump(int newpos)
{
  if (size() == 0) 
      throw std::string("empty playlist");
  while (newpos<0) {
    opts->loop--;
    newpos+=size();
  }
  if (newpos>(signed)(size()-1)) {
    if (opts->loop>0)
      opts->loop-=(int)ceil((double)newpos/(double)size());
    if (opts->loop<=0)
      throw std::string("end of playlist");
    newpos%=(size());
  }
  current=newpos;
}

void 
Playlist::addTrack( const std::string &path, const std::string filename )
{
  push_back(Track(path+filename));
  if (opts->generateTitles) {
      /* strip suffix */
      static char buf[BUFSIZ];
      assert( filename.size() < BUFSIZ );
      memcpy( buf, filename.c_str(), filename.size() );
      buf[filename.rfind( "." )] = '\0';
      (*this)[size()-1].title(buf);
  }
}

void 
Playlist::addTrack( FILE* fp )
{
  push_back(Track(fp));
}

