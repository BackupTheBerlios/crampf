/*
 * Playlist Class -- contains the playlist, handels filters
 */

#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include "playlist.hh"

Playlist::Playlist()
{
  current=0;
}

void Playlist::addPath(string path)
{
  struct stat buf;
  stat((const char*)path.c_str(),&buf);
  if (!(S_ISDIR(buf.st_mode))) {
    /* only a single file to add */
    this->push_back(Track(path));
    return;
  }
  FILE* fp;
  string findcmd = "find \"" + path + "\" -iname \"*.mp3\" -type f ";
  fp = popen((const char*)findcmd.c_str(),"r");
  if (fp==NULL) {
    perror((const char*)path.c_str());
    return;
  }
  char cbuf[MAXFILENAMELENGTH];
  while (fgets(cbuf,MAXFILENAMELENGTH,fp)) {
    cbuf[strlen(cbuf)-1]='\0'; /* strip ending '\n' */
    this->push_back(Track(cbuf));
  }
  pclose(fp);
}

void Playlist::addPath(vector<string> path)
{
  for (vector<string>::iterator it = path.begin();
      it != path.end(); it++)
    addPath(*it);
}

void Playlist::positiveFilter(string flt)
{
  for (Playlist::iterator it = this->begin();
      it != this->end(); it++) 
    if (it->filename().find(flt)==-1) 
      this->erase(it--);
}

void Playlist::positiveFilter(vector<string> flt)
{
  for (vector<string>::iterator it = flt.begin();
      it != flt.end(); it++)
    positiveFilter(*it);
}

void Playlist::negativeFilter(string flt)
{
  for (Playlist::iterator it = this->begin();
      it != this->end(); it++) 
    if (it->filename().find(flt)!=-1) 
      this->erase(it--);
}

void Playlist::negativeFilter(vector<string> flt)
{
  for (vector<string>::iterator it = flt.begin();
      it != flt.end(); it++) {
    negativeFilter(*it);
  }
}

Track Playlist::operator++()
{
  if (current+1<this->size()) {
    current++;
    return (*this)[current];
  } else
    throw string("end of playlist");
}

Track Playlist::operator--()
{
  if (current>0) {
    current--;
    return (*this)[current];
  } else
    throw string("end of playlist");
}
    
Track Playlist::operator*()
{
  return (*this)[current];
}

int Playlist::pos()
{
  return current;
}

void Playlist::jump(int newpos)
{
  current=newpos;
}

