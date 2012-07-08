#include <stumpd/load_config.hpp>
void
stumpd::
load_config ( void )
{
  // placeholder
  char *env_buf;
  env_buf = NULL;
  //env_buf = (char*)malloc(sizeof(char)*1024);

  std::cout << "^^ stumpd::load_config() ^^" << std::endl;
  env_buf = getenv("STUMPD_AUTH_TYPE");
  if(env_buf != NULL)
    stumpd::config::auth_type = strtol(env_buf, NULL, 10);
  else
    stumpd::config::auth_type = 0;
  //std::cout << "No configs to load" << std::endl;

  free(env_buf);
  
}

