//
// $Id: file.hh,v 1.1 2000/03/19 04:18:48 logic Exp $
//

#ifndef file
#define file file

#include <stdio.h>
#include <string>

class File {
  public:
    File( string filename );
    ~File();
    string operator++();
  private:
    FILE* fp;
};

#endif

