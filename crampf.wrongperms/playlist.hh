//
// $Id: playlist.hh,v 1.4 2000/03/10 18:28:35 logic Exp $
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
    void positiveFilter(string flt);
    void positiveFilter(vector<string> flt);
    void negativeFilter(string flt);
    void negativeFilter(vector<string> flt);
    Track operator++();
    Track operator--();
    Track operator*();
    int pos();
    void jump(int newpos);
  private:
    int current;
};

#endif

