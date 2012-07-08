#include <stumpd/dotcom/dotcom.hpp>

char *stumpd::dotcom::document_root;

void
stumpd::dotcom_httpd_thread_callback(void *input)
{
  ((dotcom*)input)->dotcom_eventpump.StartEventLoop();
}

void
stumpd::dotcom_onGet(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  //if(strlen(Request.URL()) == 0)
  //{  
  //  Request.SendFile(std::string(stumpd::dotcom::document_root).append("/index.html").c_str());
  //}
  ((stumpd::dotcom *)Webserver.CallbackPointer)->page_method(Webserver, Request);
 
  std::cout << "Finished a get" << std::endl;
 
  Request.Finish();
}

void
stumpd::dotcom_onPost(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{
  if(strcmp(Request.URL(), "/api"))
  {
    std::vector<const char*> params;
    //params = Request.RequestParams();
    //int i;
    //for(i=0;i<params.size();i++)
      //std::cout << "Found POST param: " << params[i] << std::endl;
    std::cout << "dotcom_onPost..." << std::endl;
    ((stumpd::dotcom *)Webserver.CallbackPointer)->page_method(Webserver, Request);
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
