//
// $Id: playlist.hh,v 1.12 2002/06/04 12:04:16 logic Exp $
//

#ifndef PLAYLIST_HH
#define PLAYLIST_HH PLAYLIST_HH

#include <string>
#include <vector>
#include <stdio.h>
#include "track.hh"

#define MAXFILENAMELENGTH 1024

class Playlist : public vector<Track>
{
  public:
    Playlist();
    void addPath( const string &path );
    void addPath( const vector<string> &path );
    void addPlaylist( string filename );
    void addPlaylist( const vector<string> &filenames );
    void savePlaylist( string filename );
    void positiveFilter( const string &flt );
    void positiveFilter( const vector<string> &flt );
    void negativeFilter( const string &flt );
    void negativeFilter( const vector<string> &flt );
    void shuffle();
    Track operator++();
    Track operator--();
    Track operator*() const;
    int pos() const;
    void jump(int newpos);
  private:
    void addTrack( const string &path, string filename );
    void addTrack(FILE* fp);
    int current;
};

#endif

