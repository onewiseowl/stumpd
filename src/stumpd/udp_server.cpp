#include <stumpd/udp_server.hpp>

void stumpd::udp_server_thread_callback(void *input)
{
  ((udp_server*)input)->udp_server_eventpump.StartEventLoop();
}

void stumpd::udp_onReceive (Lacewing::UDP &UDP, Lacewing::Address &Address, char * Data, size_t Size)
{
  fprintf(stdout, "Got UDP data %s\n", Data);
  UDP.Write(Address, Data, Size);
  return;
}
