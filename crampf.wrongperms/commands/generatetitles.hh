//
// $Id: generatetitles.hh,v 1.4 2002/06/04 12:04:18 logic Exp $
//

#ifndef GENERATETITLES_HH
#define GENERATETITLES_HH GENERATETITLES_HH

#include "../command.hh"
#include <string>

class GenerateTitles : public Command {
  public:
    void doit( const string &s );
    void help( const string &s ) const;
    void description() const;
};

#endif

