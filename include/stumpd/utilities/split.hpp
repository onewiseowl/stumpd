#ifndef SPLIT_HEADER
#define SPLIT_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

namespace stumpd {
  namespace utilities {
    std::vector < std::string > split(const char *str, char c);
  }
}

#endif
