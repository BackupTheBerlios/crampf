//
// $Id: file.hh,v 1.2 2000/03/19 09:00:23 logic Exp $
//

#ifndef file
#define file file

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

