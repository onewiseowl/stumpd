#include <stdlib.h>
#include <stdio.h>

#include <stumpd/insert.hpp>


size_t
stumpd::insert::insert_data(std::vector <std::vector <std::string> > data)
{
  size_t document_count;
  document_count = 0;


  return document_count;
}

size_t
stumpd::insert::insert_json_data(std::string json_data)
{

  // curl -D /dev/stdout -d 'action=insert&documents=[{"date":"1341941621","host":"ganja.onewiseowl.com","source":"/var/log/auth.log","content":"Jul 10 10:35:19 ganja sudo: pam_unix(sudo:session): session opened for user root by cdickey(uid=1000"}]' http://10.10.0.2:8081/api


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
  } else {

    for(document_count=0;document_count<root.size();document_count++)
    {
      document.push_back(root[document_count]["date"].asString());
      document.push_back(root[document_count]["host"].asString());
      document.push_back(root[document_count]["source"].asString());
      document.push_back(root[document_count]["content"].asString());
      data.push_back(document);
     document.clear();
    }
  }

  fprintf(stdout, "Pushed back a total of %ld elements to be inserted\n", data.size());

  return document_count;
}
