//
// $Id: file.hh,v 1.4 2002/06/01 17:27:35 logic Exp $
//

#ifndef FILE_HH
#define FILE_HH FILE_HH

#include <stdio.h>
#include <string>

class File {
  public:
    File( string filename );
    ~File();
    int linenum();
    string operator++();
  private:
    FILE* fp;
    int linenumber;
};

#endif

