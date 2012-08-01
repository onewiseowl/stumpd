#include <stumpd/dotcom/dotcom.hpp>
#include <stumpd/insert.hpp>

int
stumpd::dotcom::api_insert(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  //fprintf(stdout, "Inserting data: %s\n", Request.POST("documents"));
  if(stumpd::insert::insert_json_data(Request.POST("documents")) > 0)
  {
    Request.Status(200, "OK");
    return 0;
  } else {
    Request.Status(500, "Internal Application Error");
    return 1;
  }
}
