#pragma once

#include "MutexLock.h"
#include <pthread.h>
#include <errno.h>
#include <cstdint>
#include <time.h>

class Condition : boost::noncopyable
{
public:
    Condition(MutexLock& mutex)
        : mutex_(mutex)
    {
        pthread_cond_init(&cond_, NULL);
    }

    ~Condition()
    {
        pthread_cond_destroy(&cond_);
    }

    void wait()
    {
        pthread_cond_wait(&cond_, mutex_.get());
    }

    void notify()
    {
        pthread_cond_signal(&cond_);
    }

    void notifyAll()
    {
        pthread_cond_broadcast(&cond_);
    }

    bool waitForSeconds(unsigned int seconds)
    {
        struct timespec abtime;
        clock_gettime(CLOCK_REALTIME, &abtime);
        abtime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&cond_, mutex_.get(), &abtime);
    }

private:
    MutexLock& mutex_;
    pthread_cond_t cond_;
};
