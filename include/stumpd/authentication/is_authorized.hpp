#ifndef IS_AUTHORIZED_HEADER
#define IS_AUTHORIZED_HEADER

#include <stumpd/authentication/authentication.hpp>
#include <stumpd/authentication/authentication_session.hpp>

namespace stumpd {

template <class T>
authentication_session*
is_authorized (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request, T *obj_pointer)
{
  return
  obj_pointer->auth->ask(Request);
}

};

#endif
