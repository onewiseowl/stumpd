#include <stumpd/filters.hpp>

extern stumpd::database::mysql *mysql_conn;
extern stumpd::v8_pool *js_worker_pool;

void myReplace(std::string& str, const std::string& oldStr, const std::string& newStr)
{
  size_t pos = 0;
  while((pos = str.find(oldStr, pos)) != std::string::npos)
  {
     str.replace(pos, oldStr.length(), newStr);
     pos += newStr.length();
  }
}

int
stumpd::load_filters()
{

  std::vector <std::vector <std::string> > query_results;

  query_results =
    mysql_conn->query("SELECT filters.id, filters.filter FROM stump.filters;");
  if(query_results.size() > 0)
  {
    stumpd::filters = query_results;
    fprintf(stdout, "Got %ld filters\n", stumpd::filters.size());
    return query_results.size();
  } else {
    return query_results.size();
  }
}

std::string
stumpd::execute_filters(const char *data)
{
  size_t i;
  std::string script;

  std::string result(data);
  std::string new_result;


  //myReplace(result, "\"", "\\\"");

  stumpd::v8_pool::v8_worker *js_worker;

  js_worker = js_worker_pool->grab();

  for(i=0;i<stumpd::filters.size();i++)
  {

    new_result.clear();

    script
      .assign("var data = ")
      .append(result.c_str())
      .append(";\n")
      .append(stumpd::base64js)
      .append("\nvar filterFunction = ")
      .append(base64_decode(stumpd::filters[i][1]))
      .append("\nvar filteredOutput = filterFunction(data);\n")
      .append("JSON.stringify(filteredOutput);");

    fprintf(stdout, "Executing filter: %s\n", script.c_str());
  
    new_result.assign(js_worker->execute(script.c_str()));
    if(new_result.length() > 0)
      result.assign(new_result);  


    //fprintf(stdout, "After execution of script...\n");
  }
  js_worker->release();
  return result;
}
