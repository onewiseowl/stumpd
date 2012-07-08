#include <stumpd/dotcom/dotcom.hpp>

int
stumpd::dotcom::api_login(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  // Evaluate login credentials and set cookie if valid
  authentication_session *session;
  session = NULL;

  session = this->auth->ask(Request);
   
  if(session != NULL)
  {
    fprintf(stdout, "Authentication successful!\n");

    struct tm *tm_buf;
    char *str_time;
    str_time = (char*)malloc(sizeof(char)*30);
 
    time_t tomorrow;
    tomorrow = time(NULL) + 86400;

    tm_buf = localtime(&tomorrow);
  

    strftime(str_time, 30, "%a, %d %b %Y %H:%M:%S %Z", tm_buf);
    fprintf(stdout, "Current time is: %s\n", str_time);

    //fprintf(stdout, "api session addr is: 0x%x\n", session);
    fprintf(stdout, "api session_id is: %s\n", session->get_session_id().c_str());

    Request.Cookie(
      "session",
      std::string(
        session->get_session_id())
        .append("; Expires=")
        .append(str_time).c_str());

    Request.Status(200, "OK");
     
    free(str_time);
    //free(tm_buf);
    // shove session into active sessions map
    //this->sessions
    return 0;

  } else {
    fprintf(stdout, "Authentication unsuccessful :(\n");
    Request.Status(401, "Unauthorized");
    return 1;
  }
}

int
stumpd::dotcom::api_logout(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  if(this->auth->logout(Request) == 0)
  {
    Request.Status(200, "OK");
    return 0;
  } else {
    Request.Status(500, "Internal Server Error");
    return 1;
  }
}
