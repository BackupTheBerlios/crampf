//
// $Id: playlist.hh,v 1.1 2000/03/09 01:33:18 logic Exp $
//

#ifndef playlist
#define playlist

#include <string>
#include <vector>

#define MAXFILENAMELENGTH 1024

class Playlist : public vector<string>
{
  public:
    Playlist();
    void addPath(string path);
    void addPath(vector<string> path);
    void positiveFilter(string flt);
    void positiveFilter(vector<string> flt);
    void negativeFilter(string flt);
    void negativeFilter(vector<string> flt);
    string operator++();
    string operator--();
    string operator*();
    int pos();
    void jump(int newpos);
  private:
    int current;
};

#endif

