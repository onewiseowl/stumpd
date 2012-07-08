#ifndef LOAD_CONFIG_HEADER
#define LOAD_CONFIG_HEADER

#include <iostream>
#include <stdlib.h>
#include <string.h>

namespace stumpd {

  namespace config {
    static long int auth_type;
  }

  void
  load_config();
}

#endif
