#include <stumpd/global_fs/global_fs.hpp>
#include <strings.h>
#include <string.h>
#include <vector>


namespace stumpd {
  void
  gfs_httpd_thread_callback (void* input)
  {
    // Very simple, we just start the eventpump
    ((global_fs*)input)->gfs_eventpump.StartEventLoop(); 
  }

  void
  gfs_onGet (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
  {

    stumpd::global_fs* gfs;
    gfs = (stumpd::global_fs*)Webserver.CallbackPointer;

    std::vector<const char *> GetParams;
    //GetParams = Request.GETList();
    //GetParams = Request.RequestParams();

    authentication_session *session;
    session = NULL;

    session = stumpd::is_authorized<global_fs>(Webserver, Request, gfs);

    if(session == NULL)
    {
      //int i;
      //for(i=0;i<(int)GetParams.size();i++)
        //Request.Send(std::string("GET param: ").append(GetParams[i]).append("\n").c_str());
      Request.Send("Yeah, session is NULL\n");
    }

    Request.Finish();
    return;
  }

  void
  gfs_onPost (Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
  {
 
    stumpd::global_fs* gfs;
    gfs = (stumpd::global_fs*)Webserver.CallbackPointer;

    stumpd::is_authorized<global_fs>(Webserver, Request, gfs);

    Request.Finish();
    return;
  }

}
