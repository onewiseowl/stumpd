#ifndef DATABASE_HEADER
#define DATABASE_HEADER

#include <iostream>
#include <vector>
#include <string>

#include <stdlib.h>
#include <stdio.h>

//#include <stumpd/cache.hpp>
#include <stumpd/config.hpp>

#include <semaphore.h>
#include <mysql++.h>
#include <exceptions.h>
#define DB_TYPE "mysql"

namespace stumpd
{
namespace database
{
  class mysql
  {
    private:
    //class db_fd
    //{
      //public:
      //bool lock_fd;
      //mysqlpp::Connection *mysql_fd;
      //sem_t mutex;
      //db_fd();
      //~db_fd();
      //bool lock();
      //bool unlock();    
    //};
    //std::vector <class stumpd::database::db_fd > pool;
    class mysql_connection_pool : public mysqlpp::ConnectionPool
    {
      public:
        mysql_connection_pool(
          const char* db = "", 
          const char* server = "", 
          const char* user = "", 
          const char* password = ""
          ) : db_(db ? db : ""),
            server_(server ? server : ""),
            user_(user ? user : ""),
            password_(password ? password : "") { }
          ~mysql_connection_pool()
        {
          this->clear();
        }
          mysqlpp::Connection* create()
          {
              //std::cout.put('C'); std::cout.flush(); // indicate connection creation
              mysqlpp::Connection *tmp_conn = new mysqlpp::Connection(
                    db_.empty() ? stumpd::config::database::db_name.c_str() : 0,
                    server_.empty() ? stumpd::config::database::db_host.c_str() : 0,
                    user_.empty() ? stumpd::config::database::db_user.c_str() : 0,
                    password_.empty() ? stumpd::config::database::db_pass.c_str() : "");
              tmp_conn->set_option(new mysqlpp::MultiStatementsOption(true));
 
              return tmp_conn;

          }
        
        void destroy(mysqlpp::Connection* cp)
        {
            // Our superclass can't know how we created the Connection, so
            // it delegates destruction to us, to be safe.
            //std::cout.put('D'); std::cout.flush(); // indicate connection destruction
            delete cp;
        }

        unsigned int max_idle_time()
        {
            // Set our idle time at an example-friendly 3 seconds.  A real
            // pool would return some fraction of the server's connection
            // idle timeout instead.
            return 3;
        }

      private:
          // Our connection parameters
          std::string db_, server_, user_, password_;
      } pool;
    
    public:
    //database();
    //~database();
    //unsigned int connect();
    //unsigned int disconnect(unsigned int db_fd);
    //class stumpd::cache cache;
    template <typename T>
    std::vector <std::vector <std::string> > query(T query_string);
    static void
    escape_string(std::string &string);
  };

  template<typename T>
  std::vector <std::vector <std::string> > mysql::query(T query_string)
  //std::vector <std::vector <std::string> > stumpd::database::query(std::string query_string)
  {
    //std::vector <std::vector <std::string> > data_buf = this->cache.ask(query_string);
    std::vector <std::vector <std::string> > data_buf;
    if(data_buf.size() > 0)
    {
      // we found some relevant dater, so populate the
      // data_buf and return the goodies
      std::cout << "We found cached dater..." << data_buf.size() << std::endl;
      return data_buf;
    } else {
      try {
        mysqlpp::Connection *db_con = this->pool.grab();
        mysqlpp::StoreQueryResult results;
        if(db_con->connected() == true)
        {
          try {
            mysqlpp::Query query = db_con->query(query_string);
            results = query.store();
          } catch(mysqlpp::Exception &e) {
            fprintf(stdout, "MySQL++ Exception: %s\n", e.what());
            std::cout << "Query: " << query_string << std::endl;
            return data_buf;
          }
          fprintf(stdout, "Yay, execution completed and returned %ld rows\n", results.num_rows());
          //sleep(2);
  
          //this->pool[db_fd_i].unlock();
          unsigned int i;
          unsigned int r;
          unsigned int c;
          unsigned int ci;
          r = results.num_rows();
          data_buf.resize(r);
          if(r>0)
            c = results[0].size();
          for(i=0;i<r;i++)
          {
            for(ci=0;ci<c;ci++)
            {
              data_buf[i].push_back((std::string)results[i][ci]);
            }
          }
          this->pool.release(db_con);
          return data_buf;
        } else {
          std::cerr << "Failed to establish db descriptor lock, punting query" << std::endl;
          this->pool.release(db_con);
          return data_buf;
        }
      } catch(mysqlpp::Exception &e) {
        fprintf(stdout, "MySQL++ Exception: %s\n", e.what());
        std::cout << "Query: " << query_string << std::endl;
        return data_buf;
      }
    }
  }

  //static mysql *mysql_conn;

}
}

//static stumpd::database::mysql *mysql_conn;

#endif
