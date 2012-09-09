#ifndef SEARCH_HEADER
#define SEARCH_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <map>
#include <string>
#include <time.h>

#include <b64/base64.hpp>

#include <stumpd/database/mysql.hpp>

namespace stumpd {

  class search {

    public:

      std::vector <std::vector <std::string> >
      query(time_t from_date, time_t to_date, std::vector <std::string> hosts, std::vector <std::string> inputs, std::string query_string);

      std::string
      json_query(time_t from_date, time_t to_date, std::vector <std::string> hosts, std::vector <std::string> inputs, std::string query_string);

      std::vector <std::vector <std::string> >
      getInputs();

      std::string
      json_getInputs();

      std::vector <std::vector <std::string> >
      getHosts();

      std::string
      json_getHosts();

      std::vector <std::vector <std::string> >
      getFilters();

      std::string
      json_getFilters();

      std::string
      json_getTriggers();

      int
      addFilter(std::string alias, std::string filter);

      std::vector <std::vector <std::string> >
      getTriggers();

      int
      updateFilter(const char* alias, const char *filter, const char *id);

  };

}

#endif
