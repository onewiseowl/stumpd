namespace stumpd {
namespace config
{
#define EXCEPTION_LOG_FILENAME "/opt/stump/var/log/stumpd.log"
namespace database
{
  static std::string db_name((const char *)"stump");
  static std::string db_prefix((const char *)"");
  static std::string db_host((const char *)"127.0.0.1");
  static std::string db_user((const char *)"stump");
  static std::string db_pass((const char *)"stump");
}
}
}
