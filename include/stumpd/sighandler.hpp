#ifndef SIGHANDLER_HEADER
#define SIGHANDLER_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include <stumpd/database/mysql.hpp>

extern stumpd::database::mysql *mysql_conn;

namespace stumpd {
  void sighandler(int);
}

#endif
