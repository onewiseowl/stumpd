#include <stumpd/dotcom/dotcom.hpp>
#include <stumpd/search.hpp>

int
stumpd::dotcom::api_search(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{

  int ret;
  ret = 0;
  
  time_t from_date;
  from_date = 0;
  
  time_t to_date;
  to_date = 0;
  
  std::vector <std::string> inputs;

  std::vector <std::string> hosts;
  
  std::string query_string;

  if(strlen(Request.POST("query")) > 0)
  {
  
    query_string = Request.POST("query");

  }
  
  if(strlen(Request.POST("dateFrom")) > 0)
  {
    from_date = 
      strtol(Request.POST("dateFrom"), NULL, 0);
    
    if(strlen(Request.POST("dateTo")) > 0)
    {
      to_date = 
        strtol(Request.POST("dateTo"), NULL, 0);
          
      if(strlen(Request.POST("inputs")) > 0)
      {
        inputs = stumpd::utilities::split(Request.POST("inputs"), ',');
          
        if(strlen(Request.POST("hosts")) > 0)
        {
          hosts = stumpd::utilities::split(Request.POST("hosts"), ',');
          //fprintf(stdout, "hosts: %s\n", hosts[0].c_str());
        } else {
          fprintf(stderr, "No hosts\n");
        }

          //stumpd::search search;

          //std::string json_return =
            //search.json_query(from_date, to_date, hosts, inputs, query_string);

          //fprintf(stdout, "search.json_query returned :)\n");

          //Request.Write(json_return.c_str(), json_return.length());

          //return 0;
      } else {
          //fprintf(stderr, "No inputs\n");
      }
    } else {
      fprintf(stderr, "No to_date\n");
      return 1;
    }
  } else {
    fprintf(stderr, "No from_date\n");
    return 1;
  }
  //fprintf(stdout, "query string was empty :(\n");
  stumpd::search search;

  std::string json_return =
    search.json_query(from_date, to_date, hosts, inputs, query_string);

  //fprintf(stdout, "search.json_query returned :)\n");

  Request.Write(json_return.c_str(), json_return.length());
  return 0;
}
