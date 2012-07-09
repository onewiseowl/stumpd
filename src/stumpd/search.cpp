
#include <stumpd/search.hpp>

std::vector <std::vector <std::string> >
stumpd::search::query(time_t from_date, time_t to_date, std::vector <std::string> hosts, std::vector <std::string> sources, std::string query_string)
{

  #define DB_TYPE "mysql"
  #define DB_NAME "stump"
  #define SEARCH_LIMIT "1000"

  std::vector <std::vector <std::string> > query_results;
  struct tm *from_date_buf, *to_date_buf;


  if(strcmp(DB_TYPE, "mysql") == 0)
  {
    
    std::string mysql_query_string;

    struct tm *from_date_buf;
    struct tm *to_date_buf;

    char *year;
    year = (char *)calloc(sizeof(char), 5);
    char *year_month_day;
    year_month_day = (char *)calloc(sizeof(char), 5);
    char *epoch_from;
    epoch_from = (char *)calloc(sizeof(char), 11);
    char *epoch_to;
    epoch_to = (char *)calloc(sizeof(char), 11);

    int date_diff;
    date_diff =  ((to_date - from_date) / 86400);

    from_date_buf = localtime(&from_date);
    to_date_buf = localtime(&to_date);


    strftime(year, 5, "%Y", from_date_buf);
    strftime(year_month_day, 9, "%Y%m%d", from_date_buf);
    if(strftime(epoch_from, 11, "%s", from_date_buf) < 10)
      fprintf(stderr, "strftime error\n");

    if(strftime(epoch_to, 11, "%s", to_date_buf) < 10)
      fprintf(stderr, "strftime error\n");
    


    int a;
    int b;
    for(a=0;a<date_diff;a++);
    {
      mysql_query_string
        .append("(SELECT * FROM ")
        .append(DB_NAME)
        .append(".documents_")
        .append(year)
        .append(".")
        .append(year_month_day);

      if(sources.size() > 0)
      {
        for(b=0;b<sources.size();b++)
        {
          if(b == 0)
          {
            mysql_query_string
              .append(" WHERE source in (\"")
              .append(sources[b])
              .append("\"");   
          } else {
            mysql_query_string
              .append(",\"")
              .append(sources[b])
              .append("\"");
          }
          mysql_query_string
            .append(") ");
        }
      }

      if(sources.size() > 0)
      {
        mysql_query_string
          .append(" AND ");
      } else {
        if(hosts.size() > 0)
        {
          mysql_query_string
            .append(" WHERE ");
        }
      }

      for(b=0;b<hosts.size();b++)
      {
        if(b == 0)
        {
          mysql_query_string
            .append(" host in (\"")
            .append(sources[b])
            .append("\"");
        } else {
          mysql_query_string
            .append(",\"")
            .append(sources[b])
            .append("\"");
        }
        mysql_query_string
          .append(") ");
      }

      if(hosts.size() == 0 && sources.size() == 0)
      {
        mysql_query_string
          .append(" WHERE ");
      } else {
        mysql_query_string
          .append(" AND ");
      }

      mysql_query_string
        .append(" date>=FROM_UNIXTIME(")
        .append(epoch_from)
        .append(") AND date<=FROM_UNIXTIME(")
        .append(epoch_to)
        .append(")");

      if(query_string.length() > 0)
      {
        mysql_query_string
          .append(" AND MATCH content AGAINST('")
          .append(query_string)
          .append("' IN BOOLEAN MODE) LIMIT ")
          .append(SEARCH_LIMIT)
          .append(")");
      }
      mysql_query_string
        .append(";");

      fprintf(stdout, "Query: %s\n", mysql_query_string.c_str());

    }

    free(year);
    free(year_month_day);
    free(epoch_from);
    free(epoch_to);
    return query_results;
   } else
   if(strcmp(DB_TYPE, "clucene") == 0)
   {
     fprintf(stdout, "CLucene is not yet supported...\n");
     return query_results;
   }
}
