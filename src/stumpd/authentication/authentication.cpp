#include <stumpd/authentication/authentication.hpp>
#include <stumpd/authentication/authentication_session.hpp>

// Evaluate based on Basic auth ONLY
stumpd::authentication_session*
stumpd::authentication::ask(Lacewing::Webserver::Request& Request)
{
  std::string authorization_header(Request.Header("Authorization"));
  if(authorization_header.length() != 0)
  {
    fprintf(stdout, "Auth header is set\n");
    std::vector<std::string> split_authorization_header;
    split_authorization_header = stumpd::utilities::split(authorization_header.c_str(), ' ');

    if(split_authorization_header.size() == 2)
    {

      std::transform(split_authorization_header[0].begin(), split_authorization_header[0].end(), split_authorization_header[0].begin(), tolower);

      if(std::string("basic").compare(split_authorization_header[0]) == 0)
      {
        std::cout << "Using basic auth..." << std::endl;
        stumpd::authentication_session *session;
        //session = NULL;

        std::vector<std::string> basic_auth_split;        

        // Decode and split the username:password
        basic_auth_split = 
        stumpd::utilities::split(
          stumpd::utilities::base64::decode(split_authorization_header[1]).c_str(),
          ':');

        //std::cout << "Basic auth set as : " << stumpd::utilities::base64::decode(split_authorization_header[1]) << std::endl;

        char *md5_password;
        md5_password = (char*)malloc(sizeof(char)*33);
        memset(md5_password, '\0', 33);

        Lacewing::MD5_Hex(md5_password, basic_auth_split[1].c_str(), basic_auth_split[1].length());

        session =
        this->ask_userpass(Request, basic_auth_split[0].c_str(), md5_password);

        free(md5_password)
;
        return session;
      } else {
        // Not basic auth
        std::cout << "Not basic auth: " << split_authorization_header[0] << std::endl;
        return NULL;
      }
    } else {
      // Badly formatted Authorization request
      //std::cout << "Badly formatted Authorization request" << std::endl;
      return NULL;
    }

    } else
    // Not a cookie based login, must be a pure form based login
    if(strncmp("login", Request.POST("action"), 5) == 0)
    {
      fprintf(stdout, "POST login!\n");

      char *md5_password;
      md5_password = (char*)malloc(sizeof(char)*33);
      memset(md5_password, '\0', 33);

      Lacewing::MD5_Hex(md5_password, Request.POST("password"), strlen(Request.POST("password")));

      stumpd::authentication_session* session;
      session = this->ask_userpass(Request, Request.POST("username"), md5_password);

      free(md5_password);
      return session;
    } else
    if(strlen(Request.Cookie("session")) > 0)
    {
      fprintf(stdout, "Cookie login!\n");
      stumpd::authentication_session *session;

      session = this->ask_cookie(Request);
      //fprintf(stdout, "Cookie login session address is 0x%x\n", session);
      return session;
    } else {
      fprintf(stdout, "Nothing login---wtf?\n");
      return NULL;
    }
  return NULL;
}

stumpd::authentication_session*
stumpd::authentication::ask_userpass(Lacewing::Webserver::Request &Request, const char *username, const char *password)
{
  FILE *fp;
  char *line;
  std::string userpass;
  std::vector<std::string> split_userpass;

  line = (char*)malloc(sizeof(char)*1025);

  memset(line, 0, 1025);

  fp = fopen(STUMPD_AUTHENTICATION_HTPASSWD_FILE, "r");
  if(fp)
  {
    while((fgets(line, 1024, fp)) != NULL)
    {

      split_userpass =
        stumpd::utilities::split( 
          stumpd::utilities::base64::decode(line).c_str(),
          ':');

      if(strncmp(username, split_userpass[0].c_str(), strlen(username)) == 0)
      {
        if(strncmp(password, split_userpass[1].c_str(), strlen(password)) == 0)
        {
          stumpd::authentication_session *session;
          session = new stumpd::authentication_session(username, password);

          this->sessions.access()->insert(std::pair<const char *, stumpd::authentication_session*>(session->get_session_id().c_str(), session));
          fclose(fp);
          //free(session_id);
          free(line);

          return session;
        } else {
          fclose(fp);
          free(line);

          fprintf(stdout, "Passwords do not match %s : %s\n", password, split_userpass[1].c_str());

          return NULL;
        }
      } else {
        fprintf(stdout, "Username does not match: %s : %s\n", username, split_userpass[0].c_str());
      }
      memset(line, 0, 1025);
    }
    if(fp)
      fclose(fp);
    free(line);
    return NULL;
  } else {
    return NULL;
  }

}

stumpd::authentication_session*
stumpd::authentication::ask_cookie(Lacewing::Webserver::Request& Request)
{
  if(strlen(Request.Cookie("session")) > 0)
  {
    // Check session value against valid sessions
    if(this->sessions.access()->count(Request.Cookie("session")) > 0)
    {
      if(this->sessions.access()->find(Request.Cookie("session"))->second->get_expires() > time(NULL))
      {
        return this->sessions.access()->find(Request.Cookie("session"))->second;
      } else {
        fprintf(stdout, "Cookie is expired for session: %s\n", this->sessions.access()->find(Request.Cookie("session"))->second->get_session_id().c_str());
        delete(this->sessions.access()->find(Request.Cookie("session"))->second);
        this->sessions.access()->find(Request.Cookie("session"))->second = NULL;
        this->sessions.access()->erase(Request.Cookie("session"));
        return NULL;
      } 
    } else {
      fprintf(stdout, "No such session id in stored sessions: '%s', len: %ld, size: %ld\n", Request.Cookie("session"), strlen(Request.Cookie("session")), this->sessions.access()->size());
      return NULL;
    }
  } else {
    fprintf(stdout, "Um, session cookie is zero length\n");
    return NULL;
  }
}

stumpd::authentication_session*
stumpd::authentication::tell(Lacewing::Webserver::Request& Request)
{
  return NULL;
}

int
stumpd::authentication::load_sessions()
{
  struct dirent *file_buf, *file;
  struct stat stat_buf;
  DIR *dir;
  file_buf = (struct dirent*)malloc(pathconf(SESSION_PERSIST_PATH, _PC_NAME_MAX)*sizeof(char));
  FILE *fp;
  std::vector<std::string> split_session;
  char *session_buf;
  session_buf = (char*)malloc(sizeof(char)*1024);

  dir = opendir(SESSION_PERSIST_PATH);

  if(dir)
  {
    // readdir loop
    do {
      readdir_r(dir, file_buf, &file);
      if(file != NULL)
      {
        fprintf(stdout, "Found file: %s\n", file->d_name);
        stat(
          std::string(SESSION_PERSIST_PATH).
            append("/").
            append(file->d_name).
            c_str(),
          &stat_buf
        );

        if(S_ISREG(stat_buf.st_mode))
        {

        fp = fopen(
               std::string(SESSION_PERSIST_PATH).
                 append("/").
                 append(file->d_name).
                 c_str(),
               "r");
        if(fp)
        {
          memset((void*)session_buf, '\0', sizeof(char)*1024);
          fgets(session_buf, 1024, fp);
          fclose(fp);

          split_session.clear();
          split_session = stumpd::utilities::split(session_buf, ',');
          fprintf(stdout, "split_session size: %ld\n", split_session.size());

          this->sessions.access()->insert(
            std::pair<std::string,stumpd::authentication_session*>(
              split_session[4],
              new stumpd::authentication_session(
                strtol(split_session[0].c_str(), NULL, 10),
                strtol(split_session[1].c_str(), NULL, 10),
                strtol(split_session[2].c_str(), NULL, 10),
                split_session[3],
                split_session[4]
                )
              )
            );

          fprintf(stdout, "Just inserted stored session id %s\n", split_session[4].c_str());
          memset((void*)session_buf, '\0', sizeof(char)*1024);

          split_session.clear();
          while(split_session.size() > 0)
            split_session.pop_back();

          fprintf(stdout, "split_session members after clear: %ld\n", split_session.size());
        } else {
          fprintf(stderr, "Could not open %s session file for reading: %s\n", file->d_name, strerror(errno));
        }
      }
      }
    } while(file != NULL);
    free(file_buf);
    free(session_buf);
    closedir(dir);
    return 0;
  } else {
    fprintf(
      stderr,
      "Could not open session dir %s: %s\n",
      SESSION_PERSIST_PATH,
      strerror(errno));
    return 1;
  }
}

int
stumpd::authentication::logout(Lacewing::Webserver::Request& Request)
{
  struct stat stat_buf;
  int ret;
  ret = 0;
  
  if(strlen(Request.Cookie("session")) > 0)
  {
    std::string cookie_file(
      std::string(SESSION_PERSIST_PATH)
        .append("/")
          .append(
            Request.Cookie("session")
          )
    );
    
    stat(
      cookie_file.c_str(),
      &stat_buf
    );
    
    if(this->sessions.access()->count(Request.Cookie("session")) == 1)
    {
      this->sessions.access()->erase(Request.Cookie("session"));
    
      if(S_ISREG(stat_buf.st_mode))
      {
        ret = unlink(cookie_file.c_str());
        if(ret != 0)
        {
          fprintf(
            stderr,
            "Error unlinking session file %s : %s\n", 
            cookie_file.c_str(),
            strerror(errno)
          );
          return 1;
        } else {
         return 0;
        }
      }
    } else {
      return 0;
    }
  }
return 0;  
}
