//
// $Id: generatetitles.hh,v 1.2 2000/07/16 23:00:56 logic Exp $
//

#ifndef GENERATETITLES
#define GENERATETITLES GENERATETITLES

#include "../command.hh"
#include <string>

class GenerateTitles : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

