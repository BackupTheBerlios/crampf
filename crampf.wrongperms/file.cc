#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string>
#include "file.hh"

File::File( string filename )
{
  if (filename[0]=='~') { // replace ~ with users home
    filename.erase(filename.begin());
    filename = getenv("HOME") + filename;
  }
  fp = fopen(filename.c_str(), "r");
  if (fp==NULL)
    throw string(string("file:") + " " + string(strerror(errno)));
  linenumber = 0;
}

int
File::linenum()
{
  return linenumber;
}

string
File::operator++()
{
#define MAXLINEWIDTH 1024
  char line[MAXLINEWIDTH];
  if (fgets(line,MAXLINEWIDTH,fp)) {
    linenumber++;
    if (line[0]!='#' && line[0]!='\n') {
      line[strlen(line)-1]='\0'; /* remove '\n' */
      return line;
    } else 
      return ++(*this);
  } else
    throw string("end of file");
}

File::~File()
{
  fclose(fp);
}
