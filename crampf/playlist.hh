//
// $Id: playlist.hh,v 1.10 2000/07/16 23:10:19 logic Exp $
//

#ifndef PLAYLIST
#define PLAYLIST PLAYLIST

#include <string>
#include <vector>
#include <stdio.h>
#include "track.hh"

#define MAXFILENAMELENGTH 1024

class Playlist : public vector<Track>
{
  public:
    Playlist();
    void addPath(string path);
    void addPath(vector<string> path);
    void addPlaylist(string filename);
    void addPlaylist(vector<string> filenames);
    void savePlaylist( string filename );
    void positiveFilter(string flt);
    void positiveFilter(vector<string> flt);
    void negativeFilter(string flt);
    void negativeFilter(vector<string> flt);
    void shuffle();
    Track operator++();
    Track operator--();
    Track operator*();
    int pos();
    void jump(int newpos);
  private:
    void addTrack(string path, string filename);
    void addTrack(FILE* fp);
    int current;
};

#endif

