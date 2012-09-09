#include <stumpd/sighandler.hpp>

void
stumpd::sighandler (int sig)
{
    // cleanup
  fprintf(stdout, "Cleaning up...\n");
  delete(mysql_conn);
  delete(js_worker_pool);
  exit(0);
}
