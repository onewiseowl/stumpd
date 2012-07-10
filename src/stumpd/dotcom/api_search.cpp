#include <stumpd/dotcom/dotcom.hpp>
#include <stumpd/search.hpp>

int
stumpd::dotcom::api_search(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{

  fprintf(stdout, "API Search executed...\n");

  int ret;
  ret = 0;
  
  time_t from_date;
  from_date = 0;
  
  time_t to_date;
  to_date = 0;
  
  std::vector <std::string> sources;

  std::vector <std::string> hosts;
  
  std::string query_string;
  
  
  if(strlen(Request.POST("query_string")) > 0)
  {
  
    query_string = Request.POST("query_string");
  
    if(strlen(Request.POST("from_date")) > 0)
    {
      from_date = 
        strtoul(Request.POST("from_date"), NULL, 0);
      
      if(strlen(Request.POST("to_date")) > 0)
      {
        to_date = 
          strtoul(Request.POST("to_date"), NULL, 0);
          
        if(strlen(Request.POST("sources")) > 0)
        {
          sources = stumpd::utilities::split(Request.POST("sources"), ',');
          
          if(strlen(Request.POST("hosts")) > 0)
          {
            hosts = stumpd::utilities::split(Request.POST("hosts"), ',');
            fprintf(stdout, "hosts: %s\n", hosts[0].c_str());
          } else {
            fprintf(stderr, "No hosts\n");
          }

          stumpd::search search;

          std::string json_return =
            search.json_query(from_date, to_date, hosts, sources, query_string);

          fprintf(stdout, "search.json_query returned :)\n");

          Request.Send(json_return.c_str());          

          return 0;
        } else {
          fprintf(stderr, "No sources\n");
        }
      } else {
        fprintf(stderr, "No to_date\n");
        return 1;
      }
    } else {
      fprintf(stderr, "No from_date\n");
      return 1;
    }
  }
  fprintf(stdout, "query_string was empty :(\n");
  return 0;
}
