//
// $Id: playlist.hh,v 1.15 2002/07/02 16:28:54 logic Exp $
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
    void loadNegativeFilter( const string &filename );
    void loadPositiveFilter( const string &filename );
    void loadNegativeFilter( const vector<string> &filenames );
    void loadPositiveFilter( const vector<string> &filenames );
    void shuffle();
    Track operator++();
    Track operator++( int ) { return ++(*this); }
    Track operator--();
    Track operator*() const;
    unsigned int pos() const;
    void jump(int newpos);
  private:
    vector<string> loadFilterFile( const string &filename );
    void addTrack( const string &path, string filename );
    void addTrack(FILE* fp);
    int current;
};

#endif

