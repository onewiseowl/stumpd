#include <stumpd/dotcom/dotcom.hpp>
#include <stumpd/search.hpp>

int
stumpd::dotcom::api_updateFilter(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{

  stumpd::search search;

  if(search.updateFilter(Request.POST("alias"), Request.POST("filter"), Request.POST("id")) == 0)
  {
    Request.Status(200, "OK");
    return 0;
  } else {
    Request.Status(500, "Internal Server Error");
    return 1;
  }

  //fprintf(stdout, "search.json_query returned :)\n");
  return 0;
}
