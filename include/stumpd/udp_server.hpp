#ifndef UDP_HEADER
#define UDP_HEADER

#include <Lacewing.h>
#include <stdlib.h>
#include <stdio.h>


namespace stumpd {

  void udp_onReceive (Lacewing::UDP &UDP, Lacewing::Address &Address, char * Data, size_t Size);
  void udp_server_thread_callback(void *input);

  class udp_server {
    protected:
      Lacewing::Filter udp_server_filter;
      Lacewing::EventPump udp_server_eventpump;
      Lacewing::Thread *udp_server_thread;
      Lacewing::UDP *server;
      //friend void stumpd::dotcom_httpd_thread_callback(void *input);
      friend void stumpd::udp_onReceive (Lacewing::UDP &UDP, Lacewing::Address &Address, char * Data, size_t Size);
      friend void stumpd::udp_server_thread_callback(void *input);

    public:
      udp_server() {
        this->udp_server_filter.LocalPort(8081);
        this->udp_server_filter.Reuse(true);
        this->udp_server_filter.IPv6(false);
        this->server = new Lacewing::UDP(this->udp_server_eventpump);
        this->server->onReceive(&udp_onReceive);
        this->server->Host(this->udp_server_filter);
        this->udp_server_thread = new Lacewing::Thread("udp_server", (void*)udp_server_thread_callback);
        this->udp_server_thread->Start((void*)this);
      }

      ~udp_server() {
        if(this->server->Hosting() == true)
        {
          this->server->Unhost();
        }
        delete(this->server);
        delete(this->udp_server_thread);
      }
  };
}

#endif
