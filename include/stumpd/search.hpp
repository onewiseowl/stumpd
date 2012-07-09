#ifndef SEARCH_HEADER
#define SEARCH_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <string>
#include <time.h>

#include <stumpd/database/mysql.hpp>

namespace stumpd {

  class search {

    public:

      std::vector <std::vector <std::string> >
      query(time_t from_date, time_t to_date, std::vector <std::string> hosts, std::vector <std::string> sources, std::string query_string);

      std::string
      json_query(time_t from_date, time_t to_date, std::vector <std::string> hosts, std::vector <std::string> sources, std::string query_string);
  };

}

#endif
