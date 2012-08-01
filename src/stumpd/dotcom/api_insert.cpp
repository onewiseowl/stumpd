#include <stumpd/dotcom/dotcom.hpp>
#include <stumpd/insert.hpp>
#include <stumpd/filters.hpp>

int
stumpd::dotcom::api_insert(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  //fprintf(stdout, "Inserting data: %s\n", Request.POST("documents"));
  // first we must run filters and triggers on json data
  std::string results(stumpd::execute_filters(Request.POST("documents")));

  //stumpd::execute_triggers(Request.POST("documents"));

  if(stumpd::insert::insert_json_data(results.c_str()) > 0)
  {
    Request.Status(200, "OK");
    return 0;
  } else {
    Request.Status(500, "Internal Application Error");
    return 1;
  }
}
