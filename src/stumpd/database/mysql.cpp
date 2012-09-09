#include <stumpd/database/mysql.hpp>

void
stumpd::database::mysql::escape_string(std::string &str)
 {
   std::string escaped_string;
   if(mysqlpp::Query::escape_string(&escaped_string, str.c_str(), str.length()) > 0)
    {
      str.assign(escaped_string);
    } else {
      std::cerr << "[ ERROR ] - Error escaping MySQL string" << std::endl;
    }
 }
