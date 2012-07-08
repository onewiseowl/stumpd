#ifndef PAM_AUTH_SOURCE_HEADER
#define PAM_AUTH_SOURCE_HEADER

#include <stumpd/authentication/authentication.hpp>
#include <stumpd/authentication/authentication_session.hpp>

namespace stumpd {
  authentication_session *
  pam_auth_source(authentication* auth, const char* key, const char* value);
}
#endif
