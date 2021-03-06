#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <lacewing.h>
#include <stumpd/set_cli_opts.hpp>
#include <stumpd/load_config.hpp>
#include <stumpd/database/mysql.hpp>
#include <stumpd/global_fs/global_fs.hpp>
#include <stumpd/filters.hpp>
#include <stumpd/v8/v8.hpp>
#include <stumpd/udp_server.hpp>
// establish db connection
stumpd::database::mysql *mysql_conn = new stumpd::database::mysql();

stumpd::v8_pool *js_worker_pool = new stumpd::v8_pool(50);

//extern lwsync::critical_resource < stumpd::v8_pool*> > js_worker_pool = 
//  new stumpd::v8_pool(5);

#include <stumpd/dotcom/dotcom.hpp>
#include <stumpd/authentication/authentication.hpp>
#include <stumpd/search.hpp>
#include <stumpd/sighandler.hpp>

#include <b64/base64.hpp>

#define gettid() syscall(__NR_gettid) 

int
main( int argc, char **argv )
{

  std::cout << "returned: " << base64_encode("Sep  7 20:16:30 ganja sshd[30657]: pam_unix(sshd:auth): check pass; user unknown") << std::endl;

  signal(SIGTERM,stumpd::sighandler);
  signal(SIGQUIT,stumpd::sighandler);
  signal(SIGKILL,stumpd::sighandler);
  signal(SIGINT,stumpd::sighandler);

  
  // parse CLI options
  stumpd::set_cli_opts();
 
  // load configuration file
  stumpd::load_config();
 
  // start global fs cluster
  //stumpd::global_fs gfs;

  // start distribution queue
  //stumpd::distribution_queue dqueue;

  stumpd::load_filters();
  //stumpd::load_triggers();


  stumpd::dotcom stumpd_dotcom;
  stumpd::udp_server udpserver; 
 //std::vector <std::vector <std::string> > rows =stumpd::database::mysql_conn->query("show databases;");
  //std::cout << "count: " << rows.size() << std::endl;
  //std::cout << "rows[0].size: " << rows[0].size() << std::endl;
  //std::cout << "rows[0][rows[0].size()]: " << rows[0][rows[0].size()-1] << std::endl;

  //std::vector <std::string> test;

  //stumpd::search search;
  //search.query(time(NULL) - 86400, time(NULL), test, test, "+\"dogturds\"");

  while(1)
  {
    sleep(1);
  }
 
  delete(mysql_conn);
  
}
