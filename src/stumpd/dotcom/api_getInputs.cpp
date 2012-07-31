#include <stumpd/dotcom/dotcom.hpp>
#include <stumpd/search.hpp>

int
stumpd::dotcom::api_getInputs(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{

  stumpd::search search;

  std::string json_return =
    search.json_getInputs();

  //fprintf(stdout, "search.json_query returned :)\n");

  Request.Write(json_return.c_str(), json_return.length());

  return 0;
}