//
// $Id: playlist.hh,v 1.19 2003/01/11 16:00:41 logic Exp $
//

#ifndef PLAYLIST_HH
#define PLAYLIST_HH PLAYLIST_HH

#include <string>
#include <vector>
#include <stdio.h>
#include "track.hh"

#define MAXFILENAMELENGTH BUFSIZ

class Playlist : public std::vector<Track>
{
  public:
    Playlist();
    void addPath( const std::string &path );
    void addPath( const std::vector<std::string> &path );
    void addPlaylist( std::string filename );
    void addPlaylist( const std::vector<std::string> &filenames );
    void savePlaylist( std::string filename );
    void positiveFilter( const std::string &flt );
    void positiveFilter( const std::vector<std::string> &flt );
    void negativeFilter( const std::string &flt );
    void negativeFilter( const std::vector<std::string> &flt );
    void loadNegativeFilter( const std::string &filename );
    void loadPositiveFilter( const std::string &filename );
    void loadNegativeFilter( const std::vector<std::string> &filenames );
    void loadPositiveFilter( const std::vector<std::string> &filenames );
    void shuffle();
    Track operator++();
    Track operator++( int ) { return ++(*this); }
    Track operator--();
    Track operator--( int ) { return --(*this); }
    Track operator*() const;
    unsigned int pos() const;
    /* position defaults to current track */
    const_iterator ConstIterator( int pos = -1 ) const;
    iterator Iterator( int pos = -1 );
    void jump(int newpos);
  private:
    std::vector<std::string> loadFilterFile( const std::string &filename );
    void addTrack( const std::string &path, const std::string filename );
    void addTrack(FILE* fp);
    int current;
};

extern Playlist* plist;

#endif

