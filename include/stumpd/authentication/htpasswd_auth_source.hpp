#ifndef HTPASSWD_AUTH_SOURCE_HEADER
#define HTPASSWD_AUTH_SOURCE_HEADER

#include <stumpd/authentication/authentication.hpp>
#include <stumpd/authentication/authentication_session.hpp>

namespace stumpd {
  authentication_session *
  htpasswd_auth_source(class authentication* auth, const char* username, const char* password);
}
#endif
