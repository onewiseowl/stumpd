

#ifndef AUTHENTICATION_HEADER
#define AUTHENTICATION_HEADER

#define STUMPD_AUTHENTICATION_HTPASSWD_FILE "/tmp/stumpd.htpasswd"

#include <vector>
#include <algorithm>
#include <map>
#include <dirent.h>
#include <unistd.h>


#include <Lacewing.h>
#include <lwsync/critical_resource.hpp>
#include <lwsync/monitor.hpp>
#include <stumpd/utilities/split.hpp>
#include <stumpd/utilities/base64.hpp>
#include <stumpd/authentication/authentication_session.hpp>
#include <stumpd/authentication/is_authorized.hpp>
//#include <stumpd/authentication/authentication_sources.hpp>
#include <stumpd/authentication/htpasswd_auth_source.hpp>

#define HTPASSWD_AUTH 1
#define LDAP_AUTH 2
#define PAM_AUTH 3

namespace stumpd {

  class authentication {
    protected:
      lwsync::critical_resource < std::map<std::string,stumpd::authentication_session*> > sessions;
      authentication_session * (*auth_source)(authentication* auth, const char* key, const char* value);
      int load_sessions();
      friend authentication_session * htpasswd_auth_source(class authentication* auth, const char* username, const char* password);
      //friend int ldap_auth_source(class authentication* auth, const char* username, const char* password);
      //friend int pam_auth_source(class authentication* auth, const char* username, const char* password);
      
    public:

      authentication(const int auth_type)
      {

        this->load_sessions();

        switch(auth_type)
        {
          case HTPASSWD_AUTH:
            this->auth_source = &htpasswd_auth_source;
            break;
/*          case LDAP_AUTH:
            this->auth_source = &stumpd::ldap_auth_source;
            break;
          case PAM_AUTH:
            this->auth_source = &stumpd::pam_auth_source;
            break;
*/
          default:
            this->auth_source = &htpasswd_auth_source;
            break;
        }
      }

      ~authentication()
      {
        fprintf(stdout, "Authentication destructor is called!!!\n");
        //size_t i;

        std::map <std::string,stumpd::authentication_session*>::iterator i;

        /*
        for(i=0;i<this->sessions.access()->size();i++)
        {
          delete(this->sessions.access()->back());
          this->sessions.access()->pop_back();
        }
        */
       
        for(i=this->sessions.access()->begin();i != this->sessions.access()->end(); i++)
        {
          delete(i->second);
          i->second = NULL;
          this->sessions.access()->erase(i->first);
        }

      }

      authentication_session*
      ask(Lacewing::Webserver::Request& Request);

      authentication_session*
      ask_userpass(Lacewing::Webserver::Request& Request, const char* username, const char *password);

      authentication_session*
      ask_cookie(Lacewing::Webserver::Request& Request);

      authentication_session*
      tell(Lacewing::Webserver::Request& Request);
      
      int
      logout(Lacewing::Webserver::Request& Request);

  };
}

#endif
