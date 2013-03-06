#ifndef GLOBAL_FS_HEADER
#define GLOBAL_FS_HEADER

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <lacewing.h>

#include <stumpd/load_config.hpp>
#include <stumpd/authentication/authentication.hpp>

#include <stumpd/utilities/is_file.hpp>

#define GFS_HTTPD_PORT 8080

namespace stumpd
{

  void
  gfs_httpd_thread_callback (void* input);
  
  void
  gfs_onGet (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);
  

  class
  global_fs
  {
    protected:
    class
    global_fs_node
    {
      int id;
      std::string host;
      unsigned short int port;
      bool is_alive;

      public:
      global_fs_node(std::string _host, unsigned short int _port, bool _is_alive)
      { 
	    this->host.assign(_host);
	    this->port = _port;
	    this->is_alive = _is_alive;
	  };
      int node_id() { return this->id; };
    };
    Lacewing::Filter gfs_httpd_filter;
    Lacewing::EventPump gfs_eventpump;
    Lacewing::Webserver *gfs_webserver;
    authentication *auth;
    Lacewing::Thread *gfs_httpd_thread;
    friend void stumpd::gfs_onGet (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);
    friend void stumpd::gfs_httpd_thread_callback (void* input);
    friend authentication_session* stumpd::is_authorized<global_fs> (Lacewing::Webserver &, Lacewing::Webserver::Request &, global_fs *);
 

    public:
    std::vector<global_fs_node> nodes;

    global_fs() 
    { 
          this->auth = new stumpd::authentication(stumpd::config::auth_type);
      
          this->gfs_httpd_filter.LocalPort(GFS_HTTPD_PORT);
          this->gfs_httpd_filter.Reuse(true);

          std::cout << "Global file system enabled with " << this->nodes.size() << " members" << std::endl;	
          this->gfs_webserver = new Lacewing::Webserver(this->gfs_eventpump);
          this->gfs_webserver->CallbackPointer = (void*)this;
          this->gfs_webserver->onGet(&stumpd::gfs_onGet);
          this->gfs_webserver->EnableManualRequestFinish();

          this->gfs_webserver->Host(this->gfs_httpd_filter);
          this->gfs_httpd_thread = new Lacewing::Thread("gfs_httpd_thread_callback", (void*)&stumpd::gfs_httpd_thread_callback);
          this->gfs_httpd_thread->Start((void*)this);
          //stumpd::gfs_httpd_thread_callback((void*)this);
          //this->gfs_eventpump.StartEventLoop();
    };
    ~global_fs()
    { 
      std::cout << "Deconstructing global_fs" << std::endl;
      this->gfs_webserver->Unhost();
      delete(this->gfs_webserver);
      delete(this->gfs_httpd_thread);
      delete(this->auth);
    };
 
    //stumpd::authentication_session*
    //is_authorized(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);
  };
}

#endif 
