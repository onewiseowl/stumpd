#ifndef LDAP_AUTH_SOURCE_HEADER
#define LDAP_AUTH_SOURCE_HEADER

#include <stumpd/authentication/authentication.hpp>
#include <stumpd/authentication/authentication_session.hpp>

namespace stumpd {
  authentication_session *
  ldap_auth_source(authentication* auth, const char* key, const char* value);
}
#endif
