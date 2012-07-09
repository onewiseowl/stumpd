#include <stumpd/dotcom/dotcom.hpp>

int
stumpd::dotcom::api_search(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  int ret;
  ret = 0;
  
  unsigned long int from_date;
  from_date = 0;
  
  unsigned long int to_date;
  to_date = 0;
  
  std::string data_source;

  std::string data_source_host;
  
  std::string search_query;
  
  
  if(strlen(Request.POST("search_query")) > 0)
  {
  
    search_query = Request.POST("search_query");
  
    if(strlen(Request.POST("from_date")) > 0)
    {
      from_date = 
        strtoul(Request.POST("from_date"), NULL, 0);
      
      if(strlen(Request.POST("to_date")) > 0)
      {
        to_date = 
          strtoul(Request.POST("to_date"), NULL, 0);
          
        if(strlen(Request.POST("data_source")) > 0)
        {
          data_source = Request.POST("data_source");
          
          if(strlen(Request.POST("data_source_host")) > 0)
          {
            data_source_host = Request.POST("data_source_host");
          }
        }
      } else {
        return 1;
      }
    } else {
      return 1;
    }
  }
  
  fprintf(
    stdout,
    "search got called, here are the vars: \n %ld\n%ld\n%s\n%s\n%s\n\n",
    from_date,
    to_date,
    data_source.c_str(),
    data_source_host.c_str(),
    search_query.c_str()
  );
  
  return 0;
}
