#include "EventLoopThread.h"
#include "CommonDef.h"

EventLoopThread::EventLoopThread()
    : loop_(NULL)
    , exiting_(false)
    , thread_(std::bind(&EventLoopThread::threadFunc, this), "EventLoopThread")
    , mutex_()
    , cond_(mutex_)
{ }

EventLoopThread::~EventLoopThread()
{
    exiting_ = true;
    if (loop_ != NULL)
    {
        loop_->quit();
        thread_.join();
    }
}

EventLoop* EventLoopThread::startInLoop()
{
    thread_.start();

    {
        MutexLockGuard lock(mutex_);
        // while when loop is not NULL, and cond will notify thread to handle event
        while (loop_ == NULL)
            cond_.wait();
    }
    return loop_;
}

void EventLoopThread::threadFunc()
{
    EventLoop loop;

    {   
        MutexLockGuard lock(mutex_);
        loop_ = &loop;
        cond_.notify();
    }

    loop_->loop();
    loop_ = NULL;
}




