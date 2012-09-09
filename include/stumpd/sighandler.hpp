#ifndef SIGHANDLER_HEADER
#define SIGHANDLER_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include <stumpd/database/mysql.hpp>
#include <stumpd/v8/v8.hpp>

extern stumpd::database::mysql *mysql_conn;
extern stumpd::v8_pool *js_worker_pool;

namespace stumpd {
  void sighandler(int);
}

#endif
