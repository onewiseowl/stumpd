#ifndef STUMPD_AUTHENTICATION_SESSION_HEADER
#define STUMPD_AUTHENTICATION_SESSION_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <iostream>

#include <Lacewing.h>

#define SESSION_PERSIST_PATH "/tmp/dotcom_sessions"

namespace stumpd {

  class
  authentication_session
  {
    protected:
      const time_t created;
      time_t updated;
      std::string username;
      std::string password;
      std::string session_id;

      int
      persist();

    public:
      time_t expires;
      authentication_session(std::string new_username, std::string new_password, bool doPersist = true) :
      created(time(NULL)),
      expires(created + 86400)
      {
        username = new_username;
        password = new_password;
        char *session_id_buf, *session_id_buf_md5;
        
        session_id_buf = (char*)malloc(sizeof(char)*33);
        session_id_buf_md5 = (char*)malloc(sizeof(char)*33);
        
        memset(session_id_buf, '\0', 33);
        memset(session_id_buf_md5, '\0', 33);
        
        srand ( time(NULL) );
        
        snprintf(session_id_buf, 32, "%d%d%d%d", rand(), rand(), rand(), rand());

        lw_md5_hex(session_id_buf_md5, session_id_buf, strlen(session_id_buf));

        session_id.assign(session_id_buf);


        //this->created = time(NULL);
        //this->updated = this->created;
        //this->expires = this->created + 86400;

        free(session_id_buf);
        free(session_id_buf_md5);
     
        fprintf(stdout, "Setting this session to expire at %ld\n", this->expires);
 
        if(doPersist == true)
          this->persist();
 
      }

      
      authentication_session(const authentication_session& session) :
      created(time(NULL)),
      expires(created + 86400)
      {
        fprintf(stdout, "authentication_session copy constructor going on, and session_id is: %s\n", session.session_id.c_str());
        this->username.assign(session.username);
        this->password.assign(session.password);
        this->session_id.assign(session.session_id);
        //this->created = session.created;
        //this->updated = session.updated;
        //this->expires = session.expires;
      }
      

      
      authentication_session(
        time_t _created,
        time_t _updated,
        time_t _expires,
        std::string _username,
        std::string _session_id
      ) :
      created(_created),
      updated(_updated),
      expires(_expires)
      {
        this->username.assign(_username);
        this->session_id.assign(_session_id);
      }
      
      void
      update(std::string new_session_id);
      const time_t
      get_created(void);
      const time_t
      get_updated(void);
      const time_t
      get_expires(void);
      std::string
      get_username(void);
      std::string
      get_password(void);
      std::string
      get_session_id(void);
  };

}

#endif
