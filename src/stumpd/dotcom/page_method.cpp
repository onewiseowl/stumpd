#include <stumpd/dotcom/dotcom.hpp>

void
stumpd::dotcom::page_method(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  fprintf(stdout, "Yeah, page method got called!\n");
  // declare vars
  int ret;
  stumpd::authentication_session *session;
  struct stat stat_buf;

  // initialize vars
  ret = 0;
  session = NULL;

  if(strlen(Request.URL()) == 0 || (strlen(Request.URL()) == 1 && strncmp(Request.URL(), "/", 1) == 0))
  {  
    fprintf(stdout, "Page method index\n");
    Request.SendFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
    return;
  } else
    if(strncmp(Request.URL(), "upload", 6) == 0)
    {
      fprintf(stdout, "Page method upload\n");
      session = this->auth->ask(Request);
      if(session != NULL)
      {
        Request.SendFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
        return;
      } else
      {
        Request.Header("Location", "/login"); 
        Request.Status(302, "Object moved");
      }
    } else
    if(strncmp(Request.URL(), "login", 5) == 0)
    {
      // placeholder for dotcom login functionality, which just calls main stumpd auth methods
      Request.SendFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
      return;
    } else
    if(strncmp(Request.URL(), "logout", 6) == 0)
    {
      if(this->auth->logout(Request) == 0)
      {
        Request.Header("Location", "/login");
        Request.Status(302, "Object moved");
        return;
      } else {
        Request.Status(500, "Internal Server Error");
        return;
      }
    } else
    if(strncmp(Request.URL(), "search", 5) == 0)
    {
      session = this->auth->ask(Request);
      if(session != NULL)
      {
        Request.SendFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
        return;
      } else
      {
        Request.Header("Location", "/login");
        Request.Status(302, "Object moved");
      }
    } else
    if(strncmp(Request.URL(), "home", 4) == 0)
    {
      session = this->auth->ask(Request);
      if(session != NULL)
      {
        Request.SendFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
        return;
      } else
      {
        Request.Header("Location", "/login");
        Request.Status(302, "Object moved");
      }
    } else
    if(strncmp(Request.URL(), "api", 3) == 0)
    {
      // placeholder for dotcom API functionality (mostly just for upload/login etc)
      fprintf(stdout, "API was hit, full url is: %s\n", Request.URL());
      
      // We leave it up to the API to set Request.Status
      this->api(Webserver, Request);
    } else
    {
      fprintf(stdout, "Attempting to send file: %s\n", std::string(stumpd::dotcom::document_root).append("/").append(Request.URL()).c_str());
      // Assume that it is a file, and if so, send it
      ret = stat(std::string(stumpd::dotcom::document_root).append("/").append(Request.URL()).c_str(), &stat_buf);
      if(ret == 0)
      {
        Request.GuessMimeType(Request.URL());
        Request.SendFile(std::string(stumpd::dotcom::document_root).append("/").append(Request.URL()).c_str());
        return;
      } else {
        switch(errno)
        {
          case EACCES:
            Request.Status(403, "Forbidden");
            break;
          default:
            Request.Status(404, "Not Found");
            break;
        }
      }
    }
  
  //Request.Finish();

}
