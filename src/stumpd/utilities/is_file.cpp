#include <stumpd/utilities/is_file.hpp>

#include <iostream>

bool
is_file(const char *filename)
{
  struct stat stat_buf;
  if(stat(filename, &stat_buf) != 0)
  {
    std::cerr << "ERROR: stat() returned non zero for file: " << filename << std::endl;
    return false;
  } else {

    if(S_ISREG(stat_buf.st_mode)||
       S_ISCHR(stat_buf.st_mode)||
       S_ISBLK(stat_buf.st_mode)||
       S_ISFIFO(stat_buf.st_mode)||
       S_ISLNK(stat_buf.st_mode)) {
      return true;
    } else {
      std::cout << "Not a valid file to send: " << filename << std::endl;
      return false;
    }
  }
}
