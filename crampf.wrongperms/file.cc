#include <stdio.h>
#include <errno.h>
#include <string>
#include "file.hh"

File::File( string filename )
{
  fp = fopen(filename.c_str(), "r");
  if (fp==NULL)
    throw string(string("file:") + " " + string(strerror(errno)));
}

string
File::operator++()
{
#define MAXLINEWIDTH 1024
  char line[MAXLINEWIDTH];
  if (fgets(line,MAXLINEWIDTH,fp)) {
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
