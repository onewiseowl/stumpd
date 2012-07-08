
#ifndef LWSYNC_DETAIL_PTHREAD_FACILITIES_HPP
#define LWSYNC_DETAIL_PTHREAD_FACILITIES_HPP

#include <sys/syscall.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>

class thread_lock {
  protected:
  pthread_mutex_t _lock;

  public:
  thread_lock() {
    pthread_mutex_init(&this->_lock,NULL);
  };
  //~thread_lock();
  //void lock();
  //bool try_lock();
  //void unlock();

~thread_lock()
{
  if(this->_lock.__data.__owner == syscall(SYS_gettid))
  {
    pthread_mutex_destroy(&this->_lock);
  }
}

void lock()
{
 //pthread_mutex_lock(&this->_lock);
  this->try_lock();
}

void unlock()
{
  if(this->_lock.__data.__owner == syscall(SYS_gettid))
  { 
    pthread_mutex_unlock(&this->_lock);
  }
}

bool try_lock()
{
  if(this->_lock.__data.__owner != syscall(SYS_gettid))
  {
    pthread_mutex_lock(&this->_lock);
    return true;
  } else {
    return false;
  }
}
};

class thread_condition
{
  public:
  //void wait(thread_lock&);
void wait(thread_lock &tl)
{
  tl.lock();
}

};

namespace lwsync
{

   namespace detail
   {

      typedef thread_condition default_condition;
      typedef thread_lock default_mutex;

   } // namespace detail

} // namespace lwsync

#endif
