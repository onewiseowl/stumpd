#include <stumpd/dotcom/dotcom.hpp>
#include <sys/types.h>
#include <unistd.h>
#define gettid() syscall(__NR_gettid) 

char *stumpd::dotcom::document_root;

void
stumpd::dotcom_httpd_thread_callback(void *input)
{
  fprintf(stdout, "Before event loop...\n");
  ((dotcom*)input)->dotcom_eventpump.StartEventLoop();
  fprintf(stdout, "After event loop...\n");
}

void
stumpd::dotcom_onGet(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  //if(strlen(Request.URL()) == 0)
  //{  
  //  Request.SendFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
  //}
  ((stumpd::dotcom *)Webserver.CallbackPointer)->page_method(Webserver, Request);
 
  Request.Finish();
}

void
stumpd::dotcom_onError (Lacewing::Webserver &Webserver, Lacewing::Error &Error)
{
  fprintf(stdout, "Oops, we encountered an error: %s\n", Error.ToString());
}

void
stumpd::dotcom_onPost(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  fprintf(stdout, "We just got a POST request for \"%s\"\n", Request.URL());
  if(strncmp(Request.URL(), "api", 3) == 0)
  {
    //std::vector<const char*> params;
    //params = Request.RequestParams();
    //int i;
    //for(i=0;i<params.size();i++)
      //std::cout << "Found POST param: " << params[i] << std::endl;
    //std::cout << "dotcom_onPost..." << std::endl;
    ((stumpd::dotcom *)Webserver.CallbackPointer)->page_method(Webserver, Request);
  } else {
    Request.Status(400, "Not Found");
  }
  Request.Finish();
}


void stumpd::dotcom_onUploadPost (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request,
  Lacewing::Webserver::Upload * Uploads [], int UploadCount)
{
  int i;
  
  for(i=0;i<UploadCount;i++)
  {
    std::cout << "Just got a dotcom UPLOAD POST for file: " << Uploads[i]->GetAutoSaveFilename() << std::endl;
  }

  Request.Finish();
}

void
stumpd::dotcom_onUploadStart (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request, Lacewing::Webserver::Upload &Upload)
{
  stumpd::dotcom *stumpd_dotcom;
  stumpd_dotcom = (stumpd::dotcom*)Webserver.CallbackPointer;

  stumpd::authentication_session *session;

  session = stumpd::is_authorized<dotcom>(Webserver, Request, stumpd_dotcom);

  if(session != NULL)
  {
    Upload.SetAutoSave(); 
  } else {
    std::cout << "Unauthorized UPLOAD, setting HTTP code 401" << std::endl;
    Request.Status(401, "Authorization Required");
    Request.Header("WWW-Authenticate", "Basic realm=\"stumpd\"");
    Request.Finish();
  }

}

void
stumpd::dotcom_onUploadDone (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request, Lacewing::Webserver::Upload &Upload)
{
  //fclose(Upload.AutoSaveFile);
  int i;
  i = 0;
  i++;
}

void
stumpd::dotcom_onDisconnect (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  Request.Finish();
}
