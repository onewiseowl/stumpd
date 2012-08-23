#include <stumpd/authentication/authentication_session.hpp>

void
stumpd::authentication_session::update(std::string new_session_id)
{
  this->session_id.assign(new_session_id);
}

time_t
stumpd::authentication_session::get_created(void)
{
  return this->created;
}

time_t
stumpd::authentication_session::get_expires(void)
{
  return this->expires;
}

time_t
stumpd::authentication_session::get_updated(void)
{
  return this->updated;
}

std::string
stumpd::authentication_session::get_username(void)
{
  return this->username;
}

std::string
stumpd::authentication_session::get_password(void)
{
  return this->password;
}

std::string
stumpd::authentication_session::get_session_id(void)
{
  fprintf(stdout, "The session id thingy\n");
  fprintf(stdout, "The session id is %s\n", this->session_id.c_str());
  return std::string(this->session_id);
}

int
stumpd::authentication_session::persist()
{
  // This method persists the session data to a file
  // that the authentication object loads on init

  FILE* fp;
  struct stat stat_buf;

  if(stat(SESSION_PERSIST_PATH, &stat_buf) != 0)
  {
  //if(!S_ISDIR(stat_buf.st_mode))
    if(mkdir(SESSION_PERSIST_PATH, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP) != 0)
    {
      fprintf(
        stderr,
        "Could not create path %s: %s\n",
        SESSION_PERSIST_PATH,
        strerror(errno));
      return 1;
    }
  }

  std::string session_filename;
  session_filename.assign(SESSION_PERSIST_PATH);
  session_filename.append("/").append(this->session_id);

  fp = fopen(
         session_filename.c_str(),
         "a+");

  if(fp)
  {
    fprintf(
      fp,
      "%ld,%ld,%ld,%s,%s",
      this->created,
      this->updated,
      this->expires,
      this->username.c_str(),
      this->session_id.c_str());

    fclose(fp);

    return 0;
  } else {
    fprintf(stderr, "Error opening session persistance path %s\n", session_filename.c_str());
    return 1;
  }
}
