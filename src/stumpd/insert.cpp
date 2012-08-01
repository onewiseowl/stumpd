#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <string.h>

#include <stumpd/insert.hpp>

#define DB_TYPE "mysql"

extern stumpd::database::mysql *mysql_conn;

bool
sort_dates( std::vector <std::string>i, std::vector<std::string> j)
{

  long i_i;
  long i_j;

  i_i = strtol(i[0].c_str(), NULL, 0);
  i_j = strtol(j[0].c_str(), NULL, 0);

  return(i_i<i_j);
}


size_t
stumpd::insert::insert_data(std::vector <std::vector <std::string> > data)
{
  size_t document_count;
  document_count = 0;

  bool start;
  start = 1;

  char *ymd;
  ymd = (char*)calloc(sizeof(char), 10);

  char *ymd_old;
  ymd_old = (char*)calloc(sizeof(char), 10);

  struct tm *date_buf;
  date_buf = (struct tm*)calloc(sizeof(struct tm), 1);

  if(strcmp(DB_TYPE, "mysql") == 0)
  {

  std::string insert_query;
  std::vector <std::vector < std::string > > results;

    if(data.size() > 0)
      std::sort(data.begin(), data.end(), sort_dates);

    size_t i;
    time_t str_to_date;

    for(i=0;i<data.size();i++)
    {

      str_to_date = strtol(data[i][0].c_str(), NULL, 0);

      localtime_r(&str_to_date, date_buf);
      strftime(ymd, 10, "%Y%m%d", date_buf);

      if(strcmp(ymd, ymd_old) != 0)
      {
        if(strlen(ymd_old) != 0)
        {
          //fprintf(stdout, "ymd_old length is %ld\n", strlen(ymd_old));
          insert_query.append(";");
        } else {
          if(i<data.size()-1&&start == 0)
            insert_query.append(",");
        }
        //fprintf(stdout, "Starting new insert query, capping off the last one\n");
        start = 1;
      }
      

      if(start == 1)
      {

        strncpy(ymd_old, ymd, 10);

        insert_query
          .append("INSERT INTO `documents_")
          .append(
            std::string(ymd)
              .substr(0, 4))
          .append("`.`")
          .append(ymd)
          .append("`(date, host, input, content) VALUES ");
          start = !start;
      }

        insert_query
          .append("(FROM_UNIXTIME(")
          .append(data[i][0])
          .append("),\"")
          .append(data[i][1])
          .append("\",\"")
          .append(data[i][2])
          .append("\",\"")
          .append(data[i][3])
          .append("\")");
        //if(i<data.size()-1&&start == 0)
        //  insert_query.append(",");

    }
    fprintf(stdout, "Insert query is: %s\n", insert_query.c_str());
    results = mysql_conn->query(insert_query.c_str());
    free(ymd);
    free(ymd_old);
    if(results.size()  == 0)
      return 1;
    else
      return 0;

  } else
  if(strcmp(DB_TYPE, "clucene") == 0)
  {
    fprintf(stderr, "CLucene DB_TYPE is not yet supported\n");
    return 0;
  }


  return document_count;
}

size_t
stumpd::insert::insert_json_data(std::string json_data)
{

  // curl -D /dev/stdout -d 'action=insert&documents=[{"date":"1341941621","host":"ganja.onewiseowl.com","input":"/var/log/auth.log","content":"Jul 10 10:35:19 ganja sudo: pam_unix(sudo:session): session opened for user root by cdickey(uid=1000"}]' http://10.10.0.2:8081/api


  size_t document_count;
  document_count = 0;
  std::vector<std::string> document;

  std::vector <std::vector <std::string> > data;

  Json::Value root;   // will contains the root value after parsing.
  Json::Reader reader;
  const Json::Value APICode;

  if(!reader.parse( json_data, root ))
  {
    fprintf(stderr, "Error parsing json_data: %s\n%s\n", reader.getFormatedErrorMessages().c_str(), json_data.c_str());
    return 0;
  } else {

    for(document_count=0;document_count<root.size();document_count++)
    {
      document.push_back(root[document_count]["date"].asString());
      document.push_back(root[document_count]["host"].asString());
      document.push_back(root[document_count]["input"].asString());
      document.push_back(root[document_count]["content"].asString());
      data.push_back(document);
     document.clear();
    }
  }

  //fprintf(stdout, "Pushed back a total of %ld elements to be inserted\n", data.size());

  if(data.size() > 0)
  {
    return
    stumpd::insert::insert_data(data);
  } else {
    return 0;
  }
}
