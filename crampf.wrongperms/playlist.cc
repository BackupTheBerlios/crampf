/*
 * Playlist Class -- contains the playlist, handels filters
 */

#include "version_info.hh"
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
Playlist::addPath(string path)
{
  struct stat buf;
  stat((const char*)path.c_str(),&buf);
  if (!(S_ISDIR(buf.st_mode))) {
    /* only a single file to add */
    addTrack("",path);
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
Playlist::addPath(vector<string> path)
{
  for (vector<string>::iterator it = path.begin();
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
  for (Playlist::iterator it = this->begin();
      it != this->end(); it++)
    it->write(fp);
  fclose(fp);
}

void
Playlist::addPlaylist(string filename)
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
Playlist::addPlaylist(vector<string> filenames)
{
  for (vector<string>::iterator it = filenames.begin();
      it != filenames.end(); it++)
    addPlaylist(*it);
}

void 
Playlist::positiveFilter(string flt)
{
      int flags = REG_NOSUB;
      if (!opts->casesensivity)
	  flags = flags | REG_ICASE;
      if (opts->regexp==2)
	  flags = flags | REG_EXTENDED;
      RegEx re = RegEx( flt, flags );
      for (Playlist::iterator it = this->begin();
	      it != this->end(); it++) 
	  if ( !re.match( it->title().c_str() ) ) 
	      this->erase(it--);
}

void 
Playlist::positiveFilter(vector<string> flt)
{
  for (vector<string>::iterator it = flt.begin();
      it != flt.end(); it++)
    positiveFilter(*it);
}

void 
Playlist::negativeFilter(string flt)
{
      int flags = REG_NOSUB;
      if (!opts->casesensivity)
	  flags = flags | REG_ICASE;
      if (opts->regexp==2)
	  flags = flags | REG_EXTENDED;
      RegEx re = RegEx( flt, flags );
      for (Playlist::iterator it = this->begin();
	      it != this->end(); it++) 
	  if ( re.match( it->title().c_str() ) ) 
	      this->erase(it--);
}

void 
Playlist::negativeFilter(vector<string> flt)
{
  for (vector<string>::iterator it = flt.begin();
      it != flt.end(); it++) {
    negativeFilter(*it);
  }
}

void
Playlist::shuffle()
{
  srand(time(NULL));
  for (int i=0; i<this->size(); i++) {
    Track h = (*this)[i];
    int x = rand()%this->size();
    (*this)[i] = (*this)[x];
    (*this)[x] = h;
  }
}

Track 
Playlist::operator++()
{
  /* FIXME ++command obsolete? */
  jump(this->pos()+1);
  return (*this)[current];
}

Track 
Playlist::operator--()
{
  /* FIXME --command obsolete? */
  jump(this->pos()+1);
  return (*this)[current];
}
    
Track 
Playlist::operator*()
{
  return (*this)[current];
}

int 
Playlist::pos()
{
  return current;
}

void 
Playlist::jump(int newpos)
{
  while (newpos<0) {
    opts->loop--;
    newpos+=this->size();
  }
  if (newpos>this->size()-1) {
    if (opts->loop>0)
      opts->loop-=(int)ceil((double)newpos/(double)this->size());
    if (opts->loop<=0)
      throw string("end of playlist");
    newpos%=(this->size());
  }
  current=newpos;
}

void 
Playlist::addTrack( string path, string filename )
{
  this->push_back(Track(path+filename));
  if (opts->generateTitles) {
    filename.erase(filename.end()-4,filename.end());
    (*this)[this->size()-1].title(filename);
  }
}

void 
Playlist::addTrack( FILE* fp )
{
  this->push_back(Track(fp));
}

