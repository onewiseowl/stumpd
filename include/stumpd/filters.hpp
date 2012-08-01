#ifndef FILTERS_HEADER
#define FILTERS_HEADER

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <stumpd/database/mysql.hpp>
#include <stumpd/v8/v8.hpp>
#include <stumpd/utilities/base64.hpp>

namespace stumpd {
  static std::vector< std::vector <std::string> > filters;

  int
  load_filters();

  const char *
  execute_filters(const char *data);

}
#endif
