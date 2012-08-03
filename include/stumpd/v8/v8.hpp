#ifndef V8_POOL_HEADER
#define V8_POOL_HEADER
  
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <v8.h>

#include <lwsync/resource_accessors.hpp>
#include <lwsync/synchronization_policy.hpp>
#include <lwsync/critical_resource.hpp>
#include <lwsync/monitor.hpp>

#include <b64/cencode.h>
#include <b64/encode.h>
#include <b64/cdecode.h>
#include <b64/decode.h>

using namespace v8;

  
const char* ToCString(const v8::String::Utf8Value& value);
  
void ReportException(v8::TryCatch* try_catch);

namespace stumpd {
/* 
  class v8_worker
  {
    public:
      int release();  
  };
*/

  class v8_pool {
    public:
      v8_pool(size_t size)
      {
        size_t i;
        for(i=0;i<size;i++)
          this->workers.access()->push(new v8_pool::v8_worker);
      }
      ~v8_pool()
      {
        while(workers.access()->size()>0)
        {
          delete(this->workers.access()->front());
          workers.access()->pop();
        }
      }
  
      size_t
      size()
      {
        return this->workers.access()->size();
      }
      //TryCatch trycatch;
  
      class v8_worker {
        protected:
          // Create a new context.
          //Persistent<Context> context;
          //Context::Scope context_scope;
          //Handle<String> source; // = String::New("var test = 'Hello' + ', World!'; test;");
          //Handle<Script> script; // = Script::Compile(source);
          //HandleScope handle_scope;
          int a;  

         public:
           int
           release();
           int
           test(const char *);
           std::string
           execute(const char *);
       };

      v8_worker*
      grab();
  

    protected:
      lwsync::critical_resource < std::queue<v8_worker*> > workers;
      //lwsync::resource_sync_policy::resource_type* pool_lock_type;
      //lwsync::resource_sync_policy::locker_type* pool_lock;
      //lwsync::resource_sync_policy<> pool_lock;
      friend int v8_worker::release();
      //void
      //lock();  
      //void
      //iunlock();

  };
  
}
  
#endif
