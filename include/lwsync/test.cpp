#include <string>
#include <iostream>
#include <map>
#include <lwsync/critical_resource.hpp>
#include <lwsync/monitor.hpp>

int main(void)
{
  lwsync::critical_resource < std::map<int, std::string> > mymap;

  mymap.access()->insert(std::pair<int,std::string>(1, "Just a test"));
  std::cout << "size(): " <<   mymap.access()->size() << std::endl;
  std::cout << "value: " << mymap.access()->find(1)->second << std::endl;

  return 0;
}
