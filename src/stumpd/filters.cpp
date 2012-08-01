#include <stumpd/filters.hpp>

extern stumpd::database::mysql *mysql_conn;
extern stumpd::v8_pool *js_worker_pool;

int
stumpd::load_filters()
{

  std::vector <std::vector <std::string> > query_results;

  query_results =
    mysql_conn->query("SELECT filters.id, filters.filter FROM stump.filters;");
  if(query_results.size() > 0)
  {
    stumpd::filters = query_results;
    fprintf(stdout, "Got %d filters\n", stumpd::filters.size());
    return query_results.size();
  } else {
    return query_results.size();
  }
}

const char *
stumpd::execute_filters(const char *data)
{
  size_t i;
  std::string script;

  std::string result(data);

  stumpd::v8_pool::v8_worker *js_worker;

  js_worker_pool->grab();

  for(i=0;i<stumpd::filters.size();i++)
  {

    script
      .append("var data = ")
      .append(result.c_str())
      .append(";\nvar filterFunction = ")
      .append(stumpd::utilities::base64::decode(stumpd::filters[i][1]).c_str())
      .append("\nvar filteredOutput = filterFunction(data);\n")
      .append("filteredOutput; delete filteredOutput; delete filterFunction;");
   

    if(js_worker->test(script.c_str()) == 0)
      result.assign(js_worker->execute(script.c_str()));
    else
      return data;
  }
  js_worker->release();
  return result.c_str();
}
