#include "Thread.h"

namespace CurrentThread
{
    __thread int tCacheTid = 0;
    __thread char tidString[32];
    __thread int tidStringLen = 6;
    __thread const char* threadName = "default";
}

pid_t getTid()
{
//    return static_cast<pid_t>(::syscall(SYS_gettid));
    return static_cast<pid_t>(::syscall(__NR_gettid));
}

void CurrentThread::cacheTid()
{
    if (tCacheTid == 0)
    {
        tCacheTid = getTid();
        tidStringLen = snprintf(tidString, sizeof(tidString), "%5d", tCacheTid);
    };
}

// to keep thread name and pid
struct ThreadData
{
    typedef Thread::ThreadFunc ThreadFunc;
    ThreadFunc func_;

    std::string name_;
    pid_t* tid_;
    CountDownLatch* latch_;

    ThreadData(const ThreadFunc& func, const std::string name, pid_t* tid, CountDownLatch* latch)
        : func_(func)
        , name_(name)
        , tid_(tid)
        , latch_(latch)
    {
    }

    void runInThread()
    {
        *tid_ = CurrentThread::tid();
        tid_ = NULL;
        latch_->countDown();
        latch_ = NULL;

        CurrentThread::threadName = name_.empty() ? "thread" : name_.c_str();
        prctl(PR_SET_NAME, CurrentThread::threadName);
        func_();
        CurrentThread::threadName = "finished";
    }
};

void* startThread(void* obj)
{
    ThreadData* threadData = static_cast<ThreadData*>(obj);
    threadData->runInThread();
    delete threadData;
    return NULL;
}

Thread::Thread(const ThreadFunc& threadFunc, const std::string& name)
    : started_(false)
    , joined_(false)
    , pthread_id_(0)
    , tid_(0)
    , threadFunc_(threadFunc)
    , name_(name)
    , latch_(1)
{
    setDefaultName();
}

Thread::~Thread()
{
    // started is true but thread is still not joined
    if (started_ && !joined_)
    {
        pthread_detach(pthread_id_);
    }
}

void Thread::start()
{
    started_ = true;
    ThreadData* data = new ThreadData(threadFunc_, name_, &tid_, &latch_);

    if (pthread_create(&pthread_id_, NULL, &startThread, data))
    {
        started_ = false;
        delete data;
    }
    else
    {
        latch_.wait();
        assert(tid_ > 0);
    }
}

int Thread::join()
{
    assert(started_);
    assert(!joined_);
    joined_ = true;
    pthread_join(pthread_id_, NULL);
}

void Thread::setDefaultName()
{
    if (name_.empty())
    {
        // copy thread to buff
        char buff[32];
        snprintf(buff, sizeof(buff), "thread");
        name_ = buff;
    }
}
