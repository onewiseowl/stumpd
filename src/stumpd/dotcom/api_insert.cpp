#include <stumpd/dotcom/dotcom.hpp>
#include <stumpd/insert.hpp>

int
stumpd::dotcom::api_insert(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  if(stumpd::insert::insert_json_data(Request.POST("documents")) > 0)
    return 0;
  else
    return 1;
}
