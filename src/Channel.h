//
// Created by looperX on 2019-07-17.
//

#ifndef CPP_STUDY_CHANNEL_H
#define CPP_STUDY_CHANNEL_H

#include <iostream>
#include <functional>

// 每个channel属于一个EventLoop, 因此只属于一个线程，始终只负责一个fd的时间分发，将不同的IO事件分给不同的回调，read/write/error等。该类由其他类直接或间接调用
class EventLoop;

class Channel {
public:
    typedef std::function<void()> EventCallback;

    Channel(EventLoop* loop, int fd);
    ~Channel();

//    void handleEvent(Timestamp receiveTime);
    void handleEvent();
    void setReadCallback(EventCallback cb)
    { readCallback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb)
    { writeCallback_ = std::move(cb); }
    void setCloseCallback(EventCallback cb)
    { closeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb)
    { errorCallback_ = std::move(cb); }

    int fd() const { return fd_; }
    int events() const { return events_; }
    void set_revents(int revt) { revents_ = revt; } // used by epoll/pollers
    // int revents() const { return revents_; }
    bool isNoneEvent() const { return events_ == kNoneEvent; }

    void enableReading() { events_ |= kReadEvent; update(); }
//    void disableReading() { events_ &= ~kReadEvent; update(); }
//    void enableWriting() { events_ |= kWriteEvent; update(); }
//    void disableWriting() { events_ &= ~kWriteEvent; update(); }
//    void disableAll() { events_ = kNoneEvent; update(); }
//    bool isWriting() const { return events_ & kWriteEvent; }
//    bool isReading() const { return events_ & kReadEvent; }

    // for Poller
    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    EventLoop* ownerLoop() { return loop_; }

private:
    void update();

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;
    EventLoop* loop_;
    const int  fd_;
    int        events_;  // channel本身关心的事件
    int        revents_; // it's the received event types of epoll or poll， 目前活动的事件
    int        index_; // used by Poller.

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};


#endif //CPP_STUDY_CHANNEL_H
