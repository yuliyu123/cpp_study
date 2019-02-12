//
// Created by loohan on 2019/1/4.
//
#include "EventLoopThreadPool.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop, int threadNums)
    : baseLoop_(baseLoop)
    , threadNums_(threadNums)
    , started_(false)
    , next_(0)
{
    if (threadNums_ < 0)
    {
        perror("thread nums is less than 0, will abort");
        abort();
    }
}

void EventLoopThreadPool::start()
{
    baseLoop_->assertInLoopThread();
    started_ = true;
    for (int i = 0; i < threadNums_; i++)
    {
        std::shared_ptr<EventLoopThread> eventThread(new EventLoopThread());
        threads_.push_back(eventThread);
        loops_.push_back(eventThread->startInLoop());
    }
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
    baseLoop_->assertInLoopThread();
    assert(started_);
    EventLoop* loop = baseLoop_;

    if (!loops_.empty())
    {
        loop = loops_[next_];
        // keep event thread is equal to threadNums
        next_ = (next_ + 1) % threadNums_;
    }
    return loop;
}
