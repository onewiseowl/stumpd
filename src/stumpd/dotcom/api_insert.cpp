#include <stumpd/dotcom/dotcom.hpp>
#include <stumpd/insert.hpp>
#include <stumpd/filters.hpp>

int
stumpd::dotcom::api_insert(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  //fprintf(stdout, "Inserting data: %s\n", Request.POST("documents"));
  // first we must run filters and triggers on json data
  //fprintf(stdout, "RAW JSON to insert is: %s\n\n\n", Request.POST("documents"));

  std::string results(stumpd::execute_filters(Request.POST("documents")));

  //stumpd::execute_triggers(Request.POST("documents"));

  //if(stumpd::insert::insert_json_data(results) > 0)
  fprintf(stdout, "After filters are executed, we have a JSON result of %ld bytes\n", results.length());
  if(stumpd::insert::insert_json_data(results) > 0)
  {
    Request.Status(200, "OK");
    return 0;
  } else {
    Request.Status(500, "Internal Application Error");
    return 1;
  }
}
