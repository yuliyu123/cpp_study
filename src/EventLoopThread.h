#pragma once
#include "EventLoop.h"
#include "base/Condition.h"
#include "base/MutexLock.h"
#include "base/Thread.h"

class EventLoopThread : boost::noncopyable
{
public:
    EventLoopThread();
    ~EventLoopThread();
    EventLoop* startInLoop();

private:
    void threadFunc();
    EventLoop* loop_;
    bool exiting_;
    Thread thread_;
    MutexLock mutex_;
    Condition cond_;
};
