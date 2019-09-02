//
// Created by looperX on 2019-07-17.
//
#include <assert.h>
#include <glog/logging.h>

#include "Channel.h"
#include "Epoll.h"
#include "EventLoop.h"
#include "SocketOps.h"

const int kPollTimeMs = 10000;

EventLoop::EventLoop()
        : looping_(false),
          quit_(false),
          eventHandling_(false),
          callingPendingFunctors_(false),
          poller_(new Epoll(this)), // will fix
          wakeupFd_(createEventfd()),
//          wakeupChannel_(new Channel(this, wakeupFd_)),
//          currentActiveChannel_(nullptr)
{
    LOG(INFO) << "EventLoop created " << this << " in thread ";
    wakeupChannel_->setReadCallback(
            std::bind(&EventLoop::handleRead, this));
    // we are always reading the wakeupfd
    wakeupChannel_->enableReading();
}

// 循环处理activeChannels中活跃的事件
void EventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;
    quit_ = false;  // FIXME: what if someone calls quit() before loop() ?
    LOG(INFO) << "EventLoop " << this << " start looping";

    // quit是个标志位，不会立刻生效。此函数会不断处理activeChannels_里面的事件
    while (!quit_)
    {
        activeChannels_.clear();
        poller_->poll(kPollTimeMs, &activeChannels_);  // 获取到来的事件events
        eventHandling_ = true;
        // 遍历处理, 每个channel都有一个revents_，当前活跃时间可处理
        for (Channel* channel : activeChannels_)
        {
            currentActiveChannel_ = channel;
//            currentActiveChannel_->handleEvent(pollReturnTime_);
            currentActiveChannel_->handleEvent();
        }
        currentActiveChannel_ = NULL;
        eventHandling_ = false;
        doPendingFunctors();
    }

    LOG(INFO) << "EventLoop " << this << " stop looping";
    looping_ = false;
}

void EventLoop::runInLoop(Callback cb)
{
    if (isInLoopThread())
    {
        cb();
    }
    else
    {
        queueInLoop(std::move(cb));
    }
}

void EventLoop::queueInLoop(Callback cb)
{
    {
//        MutexLockGuard lock(mutex_);
//        std::lock_guard<std::mutex> lock(mtx_); todo
        pendingFunctors_.push_back(std::move(cb));
    }

    if (!isInLoopThread() || callingPendingFunctors_)
    {
        wakeup();
    }
}

size_t EventLoop::queueSize() const
{
//    std::lock_guard<> // mutex to protect, todo
    return pendingFunctors_.size();
}

void EventLoop::doPendingFunctors()
{
    std::vector<Callback> cbs;
    callingPendingFunctors_ = true;

    {
//        MutexLockGuard lock(mutex_);
        cbs.swap(pendingFunctors_);
    }

    for (const auto& cb : cbs)
    {
        cb();
    }
    callingPendingFunctors_ = false;
}

void EventLoop::quit()
{
    quit_ = true;
}

void EventLoop::wakeup()
{
    uint64_t one = 1;
    ssize_t n = write(wakeupFd_, &one, sizeof one);
    if (n != sizeof one)
    {
        LOG(INFO) << "EventLoop::wakeup() writes " << n << " bytes instead of 8";
    }
}

void EventLoop::handleRead()
{
    uint64_t one = 1;
    ssize_t n = read(wakeupFd_, &one, sizeof one);
    if (n != sizeof one)
    {
        LOG(INFO) << "EventLoop::handleRead() reads " << n << " bytes instead of 8";
    }
}

void EventLoop::updateChannel(Channel* channel)
{
    assert(channel->ownerLoop() == this);
    assertInLoopThread();
    poller_->updateChannel(channel);
}

EventLoop::~EventLoop()
{
    LOG(INFO) << "EventLoop::~EventLoop() destructor";
}

void EventLoop::assertInLoopThread() {
    if (!isInLoopThread())
    {
        abortNotInLoopThread();
    }
}

void EventLoop::abortNotInLoopThread() {
    LOG(INFO) << "EventLoop::abortNotInLoopThread - EventLoop " << this
              << " was created in threadId_ = " << threadId_
              << ", current thread id = " <<  std::this_thread::get_id();
}

bool EventLoop::isInLoopThread() const
{
    LOG(INFO) << "current thread: " << std::this_thread::get_id();
    return threadId_ == std::this_thread::get_id();
}
