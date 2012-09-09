#include <stumpd/dotcom/dotcom.hpp>
#include <stumpd/search.hpp>

int
stumpd::dotcom::api_addFilter(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{

  stumpd::search search;

  return search.addFilter(base64_decode(Request.POST("alias")), Request.POST("filter"));

  //fprintf(stdout, "search.json_query returned :)\n");

  //Request.Write(json_return.c_str(), json_return.length());

}
