#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string>
#include "file.hh"

File::File( std::string filename )
{
  if (filename[0]=='~') { // replace ~ with users home
    filename.erase(filename.begin());
    filename = getenv("HOME") + filename;
  }
  fp = fopen(filename.c_str(), "r");
  if (fp==NULL)
    throw std::string(std::string("file:") + " " + std::string(strerror(errno)));
  linenumber = 0;
}

int
File::linenum()
{
  return linenumber;
}

std::string
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
    throw std::string("end of file");
}

File::~File()
{
  fclose(fp);
}
