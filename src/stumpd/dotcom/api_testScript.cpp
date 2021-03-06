#include <stumpd/dotcom/dotcom.hpp>
#include <b64/base64.hpp>
#include <stumpd/v8/v8.hpp>


//extern stumpd::v8_pool *js_worker_pool;
extern stumpd::v8_pool* js_worker_pool;

int
stumpd::dotcom::api_testScript(Lacewing::Webserver &Webserver, Lacewing::Webserver::Request &Request)
{


  if(strlen(Request.POST("script")) == 0)
  {
    fprintf(stdout, "JSON is bad, script length is zero.\nRequest body is: %s\n", Request.Body());
    Request.Status(500, "Script syntax failure, length zero");
    return 1;
  }

  stumpd::v8_pool::v8_worker *js_worker = js_worker_pool->grab();

  std::string json_return;
  
  //base64::decoder b64;

  //json_return.assign(b64.decode(std::string(Request.POST("script"))));

  //fprintf(stdout, "js_worker->test() returned: %d with the following script\n%s", js_worker->test(json_return.c_str()), json_return.c_str());
  //if(js_worker->test(json_return.c_str()) == 0)
  //fprintf(stdout, "after decoding: %s\n", b64d.decode(Request.POST("script")).c_str());
  if(js_worker->test(base64_decode(std::string(Request.POST("script"))).c_str()) == 0)
  {
    Request.Status(200, "OK"); 
    Request.Write(Request.POST("script"), strlen(Request.POST("script")));
    js_worker->release();
  } else {
    Request.Status(500, "Script syntax failure");
    Request.Write(js_worker->exception(), strlen(js_worker->exception()));
    js_worker->release();
    return 1;
  }
  
  //Request.Write(json_return.c_str(), json_return.length());

  return 0;
}
