#include <stumpd/dotcom/dotcom.hpp>

void
stumpd::dotcom::page_method(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  // declare vars
  int ret;
  stumpd::authentication_session *session;
  struct stat stat_buf;
  // initialize vars
  ret = 0;
  session = NULL;

  fprintf(stdout, "Just got a request for \"%s\" : length %ld\n", Request.URL(), strlen(Request.URL()));

  fprintf(stdout, "Cookie header is %s\n", Request.Header("cookie"));

  if(strlen(Request.URL()) <= 1)// || (strlen(Request.URL()) == 1 && strncmp(Request.URL(), "/", 1) == 0))
  {  
    fprintf(stdout, "Sending index\n");
    if(this->auth->ask(Request) != NULL)
    {
      Request.Header("Location", "/search"); 
      Request.Status(302, "Object moved");
      return;
    } else {
      Request.WriteFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
      return;
    }
  } else
    if(strncmp(Request.URL(), "tools", 5) == 0)
    {
      session = this->auth->ask(Request);
      if(session != NULL)
      {
        Request.WriteFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
        return;
      } else
      {
        Request.Header("Location", "/login");
        Request.Status(302, "Object moved");
      }
  } else
    if(strncmp(Request.URL(), "upload", 6) == 0)
    {
      session = this->auth->ask(Request);
      if(session != NULL)
      {
        Request.WriteFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
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
      Request.WriteFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
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
        Request.WriteFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
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
        Request.WriteFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
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
      
      // We leave it up to the API to set Request.Status
      if(strcmp(Request.POST("action"), "login") == 0)
      {
        //fprintf(stdout, "Processing API request\n");
        this->api(Webserver, Request);
      } else {
        session = this->auth->ask(Request);
        if(session != NULL)
        {
          this->api(Webserver, Request); 
        }else {
          Request.Status(401, "Authentication Required");
        }
      }
    } else
    {
      //fprintf(stdout, "Attempting to send file: %s\n", std::string(stumpd::dotcom::document_root).append("/").append(Request.URL()).c_str());
      // Assume that it is a file, and if so, send it
      //if(Request.URL()[strlen(Request.URL()) - 1] == '?')
      //{
        //fprintf(stdout, "URL has a question mark on it\n");
        //ret = stat(std::string(stumpd::dotcom::document_root).append("/").append(std::string(Request.URL()).substr(0, strlen(Request.URL()) - 2)).c_str(), &stat_buf);
      //} else {
        //fprintf(stdout, "No question mark in URL\n");
        ret = stat(std::string(stumpd::dotcom::document_root).append("/").append(Request.URL()).c_str(), &stat_buf);
      //}

      if(ret == 0 && S_ISREG(stat_buf.st_mode))
      {
        //if(Request.URL()[strlen(Request.URL()) - 1] == '?')
        //{
        //  fprintf(stdout, "Sending file; %s\n", std::string(stumpd::dotcom::document_root).append("/").append(Request.URL()).c_str());
        //  Request.GuessMimeType(std::string(stumpd::dotcom::document_root).append("/").append(Request.URL()).c_str());
        //  Request.WriteFile(std::string(stumpd::dotcom::document_root).append("/").append(Request.URL()).c_str());
        //} else {
        //  fprintf(stdout, "No question mark in URL\n");
          //Request.WriteFile(std::string(stumpd::dotcom::document_root).append("/").append(std::string(Request.URL()).substr(0, strlen(Request.URL()) - 1)).c_str());
          Request.GuessMimeType(std::string(stumpd::dotcom::document_root).append("/").append(Request.URL()).c_str());
          Request.WriteFile(std::string(stumpd::dotcom::document_root).append("/").append(Request.URL()).c_str());
       // }

        return;
      } else {
        switch(errno)
        {
          case EACCES:
            Request.Status(403, "Forbidden");
            break;
          default:
            fprintf(stderr, "Error: %s\nError writing file: '%s'\n", strerror(errno), std::string(stumpd::dotcom::document_root).append("/").append(Request.URL()).c_str());
            Request.Status(404, "Not Found");
            break;
        }
      }
    }
  
}
