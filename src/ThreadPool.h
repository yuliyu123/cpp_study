#pragma once

#include "CommonDef.h"
#include "Channel.h"
#include <pthread.h>
#include <functional>
#include <memory>
#include <vector>
#include "base/Thread.h"


const int THREADPOOL_INVALID = -1;
const int THREADPOOL_LOCK_FAILURE = -2;
const int THREADPOOL_QUEUE_FULL = -3;
const int THREADPOOL_SHUTDOWN = -4;
const int THREADPOOL_THREAD_FAILURE = -5;
const int THREADPOOL_GRACEFUL = 1;

// default max threads is 1024, depend on server, max queue task is 65535
const int MAX_THREADS = 1024;
const int MAX_QUEUE = 65535;

typedef enum
{
    immediate_shutdown = 1,
    graceful_shutdown  = 2
} ShutDownOption;


// task to execute, invoke (task)(args)
// struct default privilege is public, but class is private, so here we use struct to define task in thread pool
struct ThreadPoolTask
{
    std::function<void(std::shared_ptr<void>)> func;
    std::shared_ptr<void> args;
};

class ThreadPool
{
public:
    static int createThreadPool(int threadCounts_, int queueSizes);
    static int addToThreadPool(std::function<void(std::shared_ptr<void>)> task, std::shared_ptr<void> args);
    static int destroyThread(ShutDownOption shutDownOption = graceful_shutdown);
    static int freeThread();
    static void *threadPoolThread(void* args);

private:
    static pthread_mutex_t mutex_;
    static pthread_cond_t notify_;

    static std::vector<pthread_t> threads_;
    static std::vector<ThreadPoolTask> queues_;
    static int head_;
    static int tail_;
    static int count_;
    static int shutDown_;
    static int started_;
    static int threadCounts_;
    static int queueSizes_;
};
