#include <stumpd/v8/v8.hpp>

const char* ToCString(const v8::String::Utf8Value& value) {
  return *value ? *value : "<string conversion failed>";
}

void ReportException(v8::TryCatch* try_catch) {
  v8::HandleScope handle_scope;
  v8::String::Utf8Value exception(try_catch->Exception());
  const char* exception_string = ToCString(exception);
  v8::Handle<v8::Message> message = try_catch->Message();
  if (message.IsEmpty()) {
    // V8 didn't provide any extra information about this error; just
    // print the exception.
    printf("%s\n", exception_string);
  } else {
    // Print (filename):(line number): (message).
    v8::String::Utf8Value filename(message->GetScriptResourceName());
    const char* filename_string = ToCString(filename);
    int linenum = message->GetLineNumber();
    printf("%s:%i: %s\n", filename_string, linenum, exception_string);
    // Print line of source code.
    v8::String::Utf8Value sourceline(message->GetSourceLine());
    const char* sourceline_string = ToCString(sourceline);
    printf("%s\n", sourceline_string);
    // Print wavy underline (GetUnderline is deprecated).
    int start = message->GetStartColumn();
    for (int i = 0; i < start; i++) {
      printf(" ");
    }
    int end = message->GetEndColumn();
    for (int i = start; i < end; i++) {
      printf("^");
    }
    printf("\n");
    v8::String::Utf8Value stack_trace(try_catch->StackTrace());
    if (stack_trace.length() > 0) {
      const char* stack_trace_string = ToCString(stack_trace);
      printf("%s\n", stack_trace_string);
    }
  }
}

stumpd::v8_pool::v8_worker*
stumpd::v8_pool::grab()
{

  Locker lock;
  lock.StartPreemption(10);
  stumpd::v8_pool::v8_worker *worker;

  //this->pool_lock.lock();

  if(this->workers.access()->size() == 0)
  {
    worker = new stumpd::v8_pool::v8_worker(this);
    //this->workers.access()->push_back(worker);
  } else {
    worker = this->workers.access()->back();
    this->workers.access()->pop_back();
  }

  //this->pool_lock.unlock();
  lock.StopPreemption();
  return worker;
}

int
stumpd::v8_pool::v8_worker::release()
{
  Locker lock;
  lock.StartPreemption(10);
  //parent->pool_lock.lock();
  parent->workers.access()->push_back(this);
  //parent->pool_lock.unlock();
  lock.StopPreemption();
  return 0;
}

int
stumpd::v8_pool::v8_worker::test(const char *script_string)
{

  //TryCatch trycatch;

  Locker lock;
  lock.StartPreemption(10);
  // Create a stack-allocated handle scope.
  HandleScope handle_scope;

  // Create a new context.
  Persistent<Context> context = Context::New();

  // Enter the created context for compiling and
  // running the hello world script. 
  Context::Scope context_scope(context);

  // Create a string containing the JavaScript source code.
  Handle<String> source = String::New(script_string);

  // Compile the source code.
  //try {
    Handle<Script> script = Script::Compile(source);
  //} catch(v8::TryCatch* try_catch) {
  //  ReportException(&trycatch);
  //  return 1;
  //}

  if(!script.IsEmpty())
  {
    lock.StopPreemption();
    context.Dispose();
    return 0;
  } else {
  //  ReportException(&trycatch);
    lock.StopPreemption();
    return 1;
  }

  fprintf(stdout, "Script: %s\n", script_string);
  lock.StopPreemption();
  return 0;
}

const char *
stumpd::v8_pool::v8_worker::execute(const char *script)
{
  fprintf(stdout, "Script: %s\n", script);
  return 0;
}
