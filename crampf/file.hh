//
// $Id: file.hh,v 1.5 2002/12/24 19:51:48 logic Exp $
//

#ifndef FILE_HH
#define FILE_HH FILE_HH

#include <stdio.h>
#include <string>

class File {
  public:
    File( std::string filename );
    ~File();
    int linenum();
    std::string operator++();
  private:
    FILE* fp;
    int linenumber;
};

#endif

