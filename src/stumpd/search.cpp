
#include <stumpd/search.hpp>
#include <unistd.h>

extern stumpd::database::mysql *mysql_conn;

std::vector <std::vector <std::string> >
stumpd::search::query(time_t from_date, time_t to_date, std::vector <std::string> hosts, std::vector <std::string> inputs, std::string query_string)
{

  #define DB_TYPE "mysql"
  #define DB_NAME "stump"
  #define SEARCH_LIMIT "1000"

  std::vector <std::vector <std::string> > query_results;
  struct tm *from_date_buf, *to_date_buf;


  if(strcmp(DB_TYPE, "mysql") == 0)
  {

    std::string mysql_query_string("");

    //struct tm *from_date_buf;
    from_date_buf = (struct tm*)calloc(sizeof(struct tm), 1);
    
    to_date_buf = (struct tm*)calloc(sizeof(struct tm), 1);

    char *year;
    year = (char *)calloc(sizeof(char), 20);
    char *year_month_day;
    year_month_day = (char *)calloc(sizeof(char), 20);
    char *epoch_from;
    epoch_from = (char *)calloc(sizeof(char), 20);
    char *epoch_to;
    epoch_to = (char *)calloc(sizeof(char), 20);

    size_t date_diff;
    date_diff =  ((to_date - from_date) / 86400);
    fprintf(stdout, "%ld days different %ld %ld\n", date_diff, to_date, from_date);

    size_t loop_count;
    loop_count = 0;
    size_t b;
    b = 0;

    for(loop_count=0;(date_diff>0)?loop_count<date_diff:loop_count<=date_diff;loop_count++)
    {

      localtime_r(&from_date, from_date_buf);
      localtime_r(&to_date, to_date_buf);

      strftime(year, 20, "%Y", from_date_buf);
      strftime(year_month_day, 20, "%Y%m%d", from_date_buf);
      if(strftime(epoch_from, 20, "%s", from_date_buf) < 10)
        fprintf(stderr, "strftime error: %s\n", epoch_from);

      if(strftime(epoch_to, 20, "%s", to_date_buf) < 10)
        fprintf(stderr, "strftime error: %s \n", epoch_to);

      mysql_query_string
        .append("(SELECT * FROM ")
        .append("`documents_")
        .append(year)
        .append("`.`")
        .append(year_month_day)
        .append("`");

      if(inputs.size() > 0)
      {
        for(b=0;b<inputs.size();b++)
        {
          if(b == 0)
          {
            mysql_query_string
              .append(" WHERE input in (\"")
              .append(inputs[b])
              .append("\"");   
          } else {
            mysql_query_string
              .append(",\"")
              .append(inputs[b])
              .append("\"");
          }
          mysql_query_string
            .append(") ");
        }
      }

      if(inputs.size() > 0)
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

      if(hosts.size() == 0 && inputs.size() == 0)
      {
        mysql_query_string
          .append(" WHERE ");
      } else {
        if(hosts.size() > 0)
        {
          mysql_query_string
            .append(" AND ");
        }
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
          .append(SEARCH_LIMIT);
          //.append(")");
      }

      mysql_query_string
        .append(")"); 

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
stumpd::search::json_query(time_t from_date, time_t to_date, std::vector <std::string> hosts, std::vector <std::string> inputs, std::string query_string)
{
  std::vector <std::vector <std::string> > search_return;
  std::string json_string("([");
  size_t a;

  search_return = this->query(from_date, to_date, hosts, inputs, query_string);

  if(search_return.size() > 0)
  {
    // table rows are as follows
    // id | date | host | input | data
    for(a=0;a<search_return.size();a++)
    {
      json_string
        .append("{date:\"")
        .append(search_return[a][1])
        .append("\",host:\"")
        .append(search_return[a][2])
        .append("\",input:\"")
        .append(search_return[a][3])
        .append("\",content:\"")
        .append(base64_encode(search_return[a][4]))
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


std::vector <std::vector <std::string> >
stumpd::search::getInputs()
{

  #define DB_TYPE "mysql"
  #define DB_NAME "stump"
  #define SEARCH_LIMIT "1000"

  std::vector <std::vector <std::string> > query_results;

  if(strcmp(DB_TYPE, "mysql") == 0)
  {
    query_results =
      mysql_conn->query("SELECT * from stump.inputs");    
    return query_results;
  } else {
    return query_results;
  }
}

std::string
stumpd::search::json_getInputs()
{

  size_t a;

  std::vector <std::vector <std::string> > search_return;
  search_return = this->getInputs();

  std::string json_string("({\"inputs\":[");

  for(a=0;a<search_return.size();a++)
  {
    json_string
      .append("\"")
      .append(search_return[a][1])
      .append("\"");
    if(a < search_return.size() - 1 && search_return.size() > 1)
        json_string.append(",");
  }
  json_string.append("]})");
  return json_string;
}

std::vector <std::vector <std::string> >
stumpd::search::getHosts()
{

  #define DB_TYPE "mysql"
  #define DB_NAME "stump"
  #define SEARCH_LIMIT "1000"

  std::vector <std::vector <std::string> > query_results;

  if(strcmp(DB_TYPE, "mysql") == 0)
  {
    query_results =
      mysql_conn->query("SELECT * from stump.hosts");    
    return query_results;
  } else {
    return query_results;
  }
}

std::string
stumpd::search::json_getHosts()
{

  size_t a;

  std::vector <std::vector <std::string> > search_return;
  search_return = this->getHosts();

  std::string json_string("({\"hosts\":[");

  for(a=0;a<search_return.size();a++)
  {
    json_string
      .append("\"")
      .append(search_return[a][1])
      .append("\"");
    if(a < search_return.size() - 1 && search_return.size() > 1)
        json_string.append(",");
  }
  json_string.append("]})");
  return json_string;
}

std::vector <std::vector <std::string> >
stumpd::search::getFilters()
{

  #define DB_TYPE "mysql"
  #define DB_NAME "stump"
  #define SEARCH_LIMIT "1000"

  std::vector <std::vector <std::string> > query_results;

  if(strcmp(DB_TYPE, "mysql") == 0)
  {
    query_results =
      mysql_conn->query("SELECT filters.id,filters.alias,filters.filter from stump.filters");    
    return query_results;
  } else {
    return query_results;
  }
}

std::string
stumpd::search::json_getFilters()
{

  size_t a;

  std::vector <std::vector <std::string> > search_return;
  search_return = this->getFilters();

  std::string json_string("[");

  for(a=0;a<search_return.size();a++)
  {
    json_string
      .append("[\"")
      .append(search_return[a][0])
      .append("\",")
      .append("\"")
      .append(search_return[a][1])
      .append("\",")
      .append("\"")
      .append(search_return[a][2])
      .append("\"]");
    if(a < search_return.size() - 1 && search_return.size() > 1)
        json_string.append(",");
  }
  json_string.append("]");
  return json_string;
}

int
stumpd::search::updateFilter(const char *alias, const char *filter, const char *id)
{

  #define DB_TYPE "mysql"
  #define DB_NAME "stump"
  #define SEARCH_LIMIT "1000"

  if(strcmp(DB_TYPE, "mysql") == 0)
  {
      mysql_conn->query(
        std::string("UPDATE stump.filters set stump.filters.alias='")
          .append(alias)
          .append("', stump.filters.filter='")
          .append(filter)
          .append("' where stump.filters.id=")
          .append(id)
          .append(";").c_str());    
    return 0;
  } else {
    return 1;
  }
}

std::vector <std::vector <std::string> >
stumpd::search::getTriggers()
{

  #define DB_TYPE "mysql"
  #define DB_NAME "stump"
  #define SEARCH_LIMIT "1000"

  std::vector <std::vector <std::string> > query_results;

  if(strcmp(DB_TYPE, "mysql") == 0)
  {
    query_results =
      mysql_conn->query("SELECT triggers.id,triggers.alias,triggers.`trigger` from stump.triggers");    
    return query_results;
  } else {
    return query_results;
  }
}

std::string
stumpd::search::json_getTriggers()
{

  size_t a;

  std::vector <std::vector <std::string> > search_return;
  search_return = this->getTriggers();

  std::string json_string("[");

  for(a=0;a<search_return.size();a++)
  {
    json_string
      .append("[\"")
      .append(search_return[a][0])
      .append("\",")
      .append("\"")
      .append(search_return[a][1])
      .append("\",")
      .append("\"")
      .append(search_return[a][2])
      .append("\"]");
    if(a < search_return.size() - 1 && search_return.size() > 1)
        json_string.append(",");
  }
  json_string.append("]");
  return json_string;
}

int
stumpd::search::addFilter(std::string alias, std::string filter)
{
  #define DB_TYPE "mysql"
  #define DB_NAME "stump"
  #define SEARCH_LIMIT "1000"

  std::vector <std::vector <std::string> > results;

  if(strcmp(DB_TYPE, "mysql") == 0)
  {
    results = 
      mysql_conn->query(
        std::string("INSERT INTO stump.filters(alias,filter) VALUES ('")
          .append(alias)
          .append("', '")
          .append(filter)
          .append("');").c_str());
    return 0;
  } else {
    return 1;
  }

}
