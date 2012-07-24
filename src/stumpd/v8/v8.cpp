#include <stumpd/v8/v8.hpp>

/*
void
stumpd::v8_pool::lock()
{
  resource_sync_policy::lock(this->pool_lock_type, this->pool_lock);
}

void
stumpd::v8_pool::unlock()
{
  resource_sync_policy::unlock(this->pool_lock_type, this->pool_lock);
}
*/

stumpd::v8_pool::v8_worker*
stumpd::v8_pool::grab()
{

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
  return worker;
}

int
stumpd::v8_pool::v8_worker::release()
{
  //parent->pool_lock.lock();
  parent->workers.access()->push_back(this);
  //parent->pool_lock.unlock();
  return 0;
}

int
stumpd::v8_pool::v8_worker::test(const char *script)
{
  fprintf(stdout, "Script: %s\n", script);
  return 0;
}

const char *
stumpd::v8_pool::v8_worker::execute(const char *script)
{
  fprintf(stdout, "Script: %s\n", script);
  return 0;
}
