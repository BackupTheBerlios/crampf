//
// $Id: playlist.hh,v 1.7 2000/03/15 08:25:32 logic Exp $
//

#ifndef playlist
#define playlist

#include <string>
#include <vector>
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
    int current;
};

#endif

