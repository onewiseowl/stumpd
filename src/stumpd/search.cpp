
#include <stumpd/search.hpp>
#include <unistd.h>

extern stumpd::database::mysql *mysql_conn;

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

    std::string mysql_query_string("");

    struct tm *from_date_buf;
    from_date_buf = (struct tm*)calloc(sizeof(struct tm), 1);
    
    struct tm *to_date_buf;
    to_date_buf = (struct tm*)calloc(sizeof(struct tm), 1);

    char *year;
    year = (char *)calloc(sizeof(char), 20);
    char *year_month_day;
    year_month_day = (char *)calloc(sizeof(char), 20);
    char *epoch_from;
    epoch_from = (char *)calloc(sizeof(char), 20);
    char *epoch_to;
    epoch_to = (char *)calloc(sizeof(char), 20);

    int date_diff;
    date_diff =  ((to_date - from_date) / 86400);

    


    int loop_count;
    loop_count = 0;
    int b;
    b = 0;

    for(loop_count=0;(date_diff>0)?loop_count<date_diff:loop_count<=date_diff;loop_count++)
    {

      localtime_r(&from_date, from_date_buf);
      localtime_r(&to_date, to_date_buf);

      strftime(year, 5, "%Y", from_date_buf);
      strftime(year_month_day, 9, "%Y%m%d", from_date_buf);
      if(strftime(epoch_from, 11, "%s", from_date_buf) < 10)
        fprintf(stderr, "strftime error\n");

      if(strftime(epoch_to, 11, "%s", to_date_buf) < 10)
        fprintf(stderr, "strftime error\n");

      mysql_query_string
        .append("(SELECT * FROM ")
        .append("documents_")
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
            .append(hosts[b])
            .append("\"");
        } else {
          mysql_query_string
            .append(",\"")
            .append(hosts[b])
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
 
      if(date_diff > 0 && loop_count+1<date_diff)
      mysql_query_string.append(" UNION ");

      from_date = from_date + 86400;
    }

   //fprintf(stdout, "Query: %s\n", mysql_query_string.c_str());

    query_results =
      mysql_conn->query(mysql_query_string.c_str());

    free(year);
    free(year_month_day);
    free(epoch_from);
    free(epoch_to);
    free(from_date_buf);
    free(to_date_buf);
    return query_results;
   } else
   if(strcmp(DB_TYPE, "clucene") == 0)
   {
     fprintf(stdout, "CLucene is not yet supported...\n");
     return query_results;
   }
}

std::string
stumpd::search::json_query(time_t from_date, time_t to_date, std::vector <std::string> hosts, std::vector <std::string> sources, std::string query_string)
{
  std::vector <std::vector <std::string> > search_return;
  std::string json_string("([");
  size_t a;
  size_t b;

  search_return = this->query(from_date, to_date, hosts, sources, query_string);

  if(search_return.size() > 0)
  {
    // table rows are as follows
    // id | date | host | source | data
    for(a=0;a<search_return.size();a++)
    {
      json_string
        .append("{date:\"")
        .append(search_return[a][1])
        .append("\",host:\"")
        .append(search_return[a][2])
        .append("\",source:\"")
        .append(search_return[a][3])
        .append("\",content:\"")
        .append(search_return[a][4])
        .append("\"}");

      if(a < search_return.size() - 1 && search_return.size() > 1)
        json_string.append(",");
    }

    json_string.append("])");

    //fprintf(stdout, "json_string: %s\n", json_string.c_str());
    return json_string;
  } else {
    //fprintf(stderr, "search_return.size(): %ld\n", search_return.size());
    return std::string("([])");
  }

}
