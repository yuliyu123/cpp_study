//
// Created by loohan on 2019/1/4.
//

#ifndef CPP_STUDY_EVENTLOOPPOOL_H
#define CPP_STUDY_EVENTLOOPPOOL_H

#include "EventLoop.h"
#include "ThreadPool.h"
#include "EventLoopThread.h"

class EventLoopThreadPool
{
public:
    EventLoopThreadPool(EventLoop* loop, int threadNums);
    ~EventLoopThreadPool()
    {
        // close eventthreadpool
    }

    void start();
    EventLoop* getNextLoop();

private:
    // single thread use baseloop
    EventLoop* baseLoop_;
    int threadNums_;
    bool started_;
    int next_;
    std::vector<std::shared_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;
};

#endif //CPP_STUDY_EVENTLOOPPOOL_H
