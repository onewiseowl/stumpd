#include <stumpd/dotcom/dotcom.hpp>

void
stumpd::dotcom::api(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  // This is just a test response
  if(strcmp(Request.POST("action"), "getSources") == 0)
  {
    Request.Send("[{\"/var/www/verifi/logs/stuff/stuff.log\", \"/var/log/auth.log\"}]");
    return;
  }

  if(strcmp(Request.POST("action"), "search") == 0)
  {
    this->api_search(Webserver, Request);
  } else
  if(strcmp(Request.POST("action"), "login") == 0)
  {
    this->api_login(Webserver, Request);
  } else
  if(strcmp(Request.POST("action"), "logout") == 0 || strcmp(Request.URL(), "logout") == 0)
  {
    // This is a cookie style logout
    this->api_logout(Webserver, Request);
  } else {
    fprintf(stdout, "Not a known api action\n");
  }
}
