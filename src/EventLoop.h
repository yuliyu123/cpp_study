//
// Created by looperX on 2019-07-17.
//

#ifndef CPP_STUDY_EVENTLOOP_H
#define CPP_STUDY_EVENTLOOP_H

#include <atomic>
#include <functional>
#include <iostream>
#include <vector>
#include <thread>
#include <memory>

#include "EventLoopBase.h"

class Channel;
class Epoll;

// 每个 EventLoop class 拥有一个线程
class EventLoop {
public:
    typedef std::function<void()> Callback;

    EventLoop();
    ~EventLoop();

    // force out-line dtor, for std::unique_ptr members.

    ///
    /// Loops forever.
    ///
    /// Must be called in the same thread as creation of the object.
    ///
    void loop();
    void quit();
    void runInLoop(Callback cb);
    void queueInLoop(Callback cb);
    size_t queueSize() const;
    void doPendingFunctors();
    bool isInLoopThread() const;
    void assertInLoopThread();
    void wakeup();
    void handleRead();
    void updateChannel(Channel* channel);

    int runAt(timer_callback cb, void* args, uint64_t ts);
    int runAfter(timer_callback cb, void* args, int sec, int millis);
    int runEvery(timer_callback cb, void* args, int sec, int millis);

private:
    void abortNotInLoopThread();
    typedef std::vector<Channel*> ChannelList;

    bool looping_; /* atomic */
    std::atomic<bool> quit_;
    bool eventHandling_; /* atomic */
    bool callingPendingFunctors_; /* atomic */
//    std::mutex mtx_;  // todo
//    const pid_t threadId_;
    const std::thread::id threadId_;
    std::unique_ptr<Epoll> poller_;
    int wakeupFd_;
    std::vector<Callback> pendingFunctors_;
    std::unique_ptr<Channel> wakeupChannel_;

    // scratch variables
    ChannelList activeChannels_;
    Channel* currentActiveChannel_;
};


#endif //CPP_STUDY_EVENTLOOP_H
