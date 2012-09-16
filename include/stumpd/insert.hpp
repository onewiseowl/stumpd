#ifndef INSERT_HEADER
#define INSERT_HEADER

#include <iostream>
#include <string>
#include <vector>
#include <jsonpp/reader.h>
#include <jsonpp/writer.h>

#include <stumpd/database/mysql.hpp>

namespace stumpd {

  //class insert {
  namespace insert {

    //public:

      size_t
      insert_data(std::vector <std::vector <std::string> > data);
      //static insert_data(std::vector <std::vector <std::string> > data);

      size_t
      insert_json_data(std::string json_data);
      //static insert_json_data(std::string json_data);

  //};
  }

}

#endif
