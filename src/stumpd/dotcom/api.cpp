#include <stumpd/dotcom/dotcom.hpp>

void
stumpd::dotcom::api(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  if(strcmp(Request.GET("action"), "getSources") == 0)
  {
    Request.Send("[{\"/var/www/verifi/logs/stuff/stuff.log\", \"/var/log/auth.log\"}]");
    return;
  }

  if(strcmp(Request.POST("action"), "search") == 0)
  {
    //stump::dotcom::api_search(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
    Request.Send(std::string("search: ").append(Request.POST("json")).c_str());
    return;
  }

  if(strcmp(Request.POST("action"), "login") == 0)
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


    } else {
      fprintf(stdout, "Authentication unsuccessful :(\n");
      Request.Status(401, "Unauthorized");
    }
  } else
  if(strcmp(Request.POST("action"), "logout") == 0 || strcmp(Request.URL(), "logout") == 0)
  {
    // This is a cookie style logout
    this->auth->logout(Request);
  } else {
    fprintf(stdout, "Not a known api action\n");
  }
}
