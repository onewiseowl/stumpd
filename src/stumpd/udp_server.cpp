#include <stumpd/udp_server.hpp>
#include <stumpd/utilities/split.hpp>

void stumpd::udp_server_thread_callback(void *input)
{
  ((udp_server*)input)->udp_server_eventpump.StartEventLoop();
}

void stumpd::udp_onReceive (Lacewing::UDP &UDP, Lacewing::Address &Address, char * Data, size_t Size)
{
  fprintf(stdout, "Got UDP data of %ld bytes\n", Size);
  //UDP.Write(Address, Data, Size);
  UDP.Write(Address, "Got data!\0", sizeof(char)*10); 
  return;
}
