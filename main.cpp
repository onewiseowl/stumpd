#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <Lacewing.h>
#include <stumpd/set_cli_opts.hpp>
#include <stumpd/load_config.hpp>
#include <stumpd/database/mysql.hpp>
#include <stumpd/global_fs/global_fs.hpp>

// establish db connection
extern stumpd::database::mysql *mysql_conn =
  new stumpd::database::mysql();

#include <stumpd/dotcom/dotcom.hpp>
#include <stumpd/authentication/authentication.hpp>
#include <stumpd/search.hpp>
#include <stumpd/sighandler.hpp>

#define gettid() syscall(__NR_gettid) 

int
main( int argc, char **argv )
{

  signal(SIGTERM,stumpd::sighandler);
  signal(SIGQUIT,stumpd::sighandler);
  signal(SIGKILL,stumpd::sighandler);
  signal(SIGINT,stumpd::sighandler);

  
  fprintf(stdout, "Parent PID %d\n", gettid());
  
  // parse CLI options
  stumpd::set_cli_opts();
 
  // load configuration file
  stumpd::load_config();
 
  // start global fs cluster
  //stumpd::global_fs gfs;

  // start distribution queue
  //stumpd::distribution_queue dqueue;


  fprintf(stdout, "*stumpd::database::myql_conn = %0x%x\n", mysql_conn);

  stumpd::dotcom stumpd_dotcom;
  //std::vector <std::vector <std::string> > rows =stumpd::database::mysql_conn->query("show databases;");
  //std::cout << "count: " << rows.size() << std::endl;
  //std::cout << "rows[0].size: " << rows[0].size() << std::endl;
  //std::cout << "rows[0][rows[0].size()]: " << rows[0][rows[0].size()-1] << std::endl;

  //std::vector <std::string> test;

  //stumpd::search search;
  //search.query(time(NULL) - 86400, time(NULL), test, test, "+\"dogturds\"");

  fprintf(stdout, "After dotcom\n");

  while(1)
  {
    sleep(1);
  }
 
  delete(mysql_conn);
  
}
