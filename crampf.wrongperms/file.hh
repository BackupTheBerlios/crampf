//
// $Id: file.hh,v 1.3 2000/07/16 23:10:19 logic Exp $
//

#ifndef FILE
#define FILE FILE

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

