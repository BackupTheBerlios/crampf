//
// $Id: generatetitles.hh,v 1.5 2002/12/24 19:51:50 logic Exp $
//

#ifndef GENERATETITLES_HH
#define GENERATETITLES_HH GENERATETITLES_HH

#include "../command.hh"
#include <string>

class GenerateTitles : public Command {
  public:
    void doit( const std::string &s );
    void help( const std::string &s ) const;
    void description() const;
};

#endif

