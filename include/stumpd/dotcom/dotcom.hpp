#ifndef DOTCOM_HEADER
#define DOTCOM_HEADER

#define DOTCOM_HTTPD_PORT 8081

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <iostream>

#include <Lacewing.h>

#include <stumpd/authentication/authentication.hpp>
#include <stumpd/load_config.hpp>
#include <stumpd/utilities/is_file.hpp>
#include <stumpd/utilities/split.hpp>

namespace stumpd {

  void
  dotcom_httpd_thread_callback(void *input);

  void
  dotcom_onGet(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);

  void
  dotcom_onPost(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);

  void
  dotcom_onUploadPost (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request,
    Lacewing::Webserver::Upload * Uploads [], int UploadCount);

  void
  dotcom_onUploadStart (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request,
    Lacewing::Webserver::Upload &Upload);

  void dotcom_onUploadDone (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request,
    Lacewing::Webserver::Upload &Upload);

  class dotcom {
    protected:
      Lacewing::Filter dotcom_httpd_filter;
      Lacewing::EventPump dotcom_eventpump;
      Lacewing::Webserver *dotcom_webserver;
      Lacewing::Thread *dotcom_httpd_thread;
      authentication *auth;

      void
      page_method(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);
      
      // Beginning of API method definitions
      
      int
      api_login(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);
      
      int
      api_logout(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);
      
      int
      api_search(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);
      
      int
      api_insert(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);

      int
      api_insert_data(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);

      int
      api_getInputs(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);

      int
      api_getHosts(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);

      int
      api_testScript(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);
      
      int
      api_getFilters(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);

      int
      api_getTriggers(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);

      int
      api_updateFilter(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);

      void
      api(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);
      
      friend void stumpd::dotcom_httpd_thread_callback(void *input);
      friend void stumpd::dotcom_onGet(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);
      friend void stumpd::dotcom_onPost(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request);
      friend authentication_session* stumpd::is_authorized<dotcom> (Lacewing::Webserver &, Lacewing::Webserver::Request &, dotcom *);

    public:
     static char* document_root;
      dotcom()
      {

        this->auth = new stumpd::authentication(stumpd::config::auth_type);

        stumpd::dotcom::document_root = (char*)malloc(sizeof(char)*1024);
        memset(stumpd::dotcom::document_root, 0, 1024);
        getcwd(stumpd::dotcom::document_root, 1024);
        strcat(stumpd::dotcom::document_root, "/www");

        this->dotcom_httpd_filter.LocalPort(DOTCOM_HTTPD_PORT);
        this->dotcom_httpd_filter.Reuse(true);
        this->dotcom_httpd_filter.IPv6(false);

        this->dotcom_httpd_thread = new Lacewing::Thread("dotcom_httpd_thread", (void*)dotcom_httpd_thread_callback);
        this->dotcom_webserver = new Lacewing::Webserver(this->dotcom_eventpump);
        this->dotcom_webserver->CallbackPointer = (void*)this;
        
        this->dotcom_webserver->EnableManualRequestFinish();

        this->dotcom_webserver->onGet(dotcom_onGet);
        this->dotcom_webserver->onPost(dotcom_onPost);
        this->dotcom_webserver->onUploadPost(dotcom_onUploadPost);
        this->dotcom_webserver->onUploadStart(dotcom_onUploadStart);
        this->dotcom_webserver->onUploadDone(dotcom_onUploadDone);

        this->dotcom_webserver->Host(this->dotcom_httpd_filter);

        this->dotcom_httpd_thread->Start((void*)this);

      }

      ~dotcom()
      {
        fprintf(stdout, "Deleting dotcom\n");
        delete(this->dotcom_httpd_thread);
        delete(this->auth);
        free(this->document_root);
      }
  };

}

#endif
