//
// $Id: generatetitles.hh,v 1.3 2002/06/01 17:27:37 logic Exp $
//

#ifndef GENERATETITLES_HH
#define GENERATETITLES_HH GENERATETITLES_HH

#include "../command.hh"
#include <string>

class GenerateTitles : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

