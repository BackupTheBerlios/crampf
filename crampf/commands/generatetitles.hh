//
// $Id: generatetitles.hh,v 1.1 2000/03/18 13:48:07 logic Exp $
//

#ifndef generatetitles
#define generatetitles generatetitles

#include "../command.hh"
#include <string>

class GenerateTitles : public Command {
  public:
    void doit( string s );
    void help( string s );
    void description();
};

#endif

