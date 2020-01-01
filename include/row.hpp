#pragma once
#include "util.hpp"
#include <pthread.h>

template<typename PayloadT>
class Row { 
  private:
    uint64_t _version = 0;
#ifndef USE_RTM
    pthread_spinlock_t _lock;
#endif
  public:
    PayloadT payload;

    Row() {
#ifndef USE_RTM
      pthread_spin_init(&_lock, 0);
#endif
    }
    inline uint64_t get_version() const {return _version;}
    inline void inc_version() {_version++;}
    inline void lock() {
#ifndef USE_RTM
      pthread_spin_lock(&_lock);
#endif
    }
    inline void unlock() {
#ifndef USE_RTM
      pthread_spin_unlock(&_lock);
#endif
    }
};