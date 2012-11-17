#include <stumpd/dotcom/dotcom.hpp>

void
stumpd::dotcom::api(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{

  //fprintf(stdout, "Executing API function...\n");

  // This is just a test response
  if(strcmp(Request.Header("x-stump-action"), "ping") == 0)
  {
    return;
  } else
  if(strcmp(Request.Header("x-stump-action"), "testScript") == 0)
  {
    this->api_testScript(Webserver, Request);
    return;
  } else
  if(strcmp(Request.Header("x-stump-action"), "getTriggers") == 0)
  {
    this->api_getTriggers(Webserver, Request);
    return;
  } else
  if(strcmp(Request.Header("x-stump-action"), "getFilters") == 0)
  {
    this->api_getFilters(Webserver, Request);
    return;
  } else
  if(strcmp(Request.Header("x-stump-action"), "updateFilter") == 0)
  {
    this->api_updateFilter(Webserver, Request);
    return;
  } else
  if(strcmp(Request.Header("x-stump-action"), "addFilter") == 0)
  {
    if(this->api_addFilter(Webserver, Request) == 0)
      return;
    else
      Request.Status(500, "Internal Server Error");

    return;
  } else
  if(strcmp(Request.Header("x-stump-action"), "getInputs") == 0)
  {
    //Request.Write("[{\"/var/www/verifi/logs/stuff/stuff.log\", \"/var/log/auth.log\"}]");
    this->api_getInputs(Webserver, Request);
    return;
  } else
  if(strcmp(Request.Header("x-stump-action"), "getHosts") == 0)
  {
    //Request.Write("[{\"/var/www/verifi/logs/stuff/stuff.log\", \"/var/log/auth.log\"}]");
    this->api_getHosts(Webserver, Request);
    return;
  } else
  if(strcmp(Request.Header("x-stump-action"), "search") == 0)
  {
    this->api_search(Webserver, Request);
  } else
  if(strcmp(Request.Header("x-stump-action"), "insert") == 0)
  {
    //fprintf(stdout, "About to execute api_insert\n");
    this->api_insert(Webserver, Request);
  } else
  if(strcmp(Request.Header("x-stump-action"), "login") == 0)
  {
    this->api_login(Webserver, Request);
  } else
  if(strcmp(Request.Header("x-stump-action"), "logout") == 0 || strcmp(Request.URL(), "logout") == 0)
  {
    // This is a cookie style logout
    this->api_logout(Webserver, Request);
  } else {
    fprintf(stderr, "Not a known api action: %s\n", Request.Header("x-stump-action"));
    Request.Status(404, "Not Found");
  }
}
