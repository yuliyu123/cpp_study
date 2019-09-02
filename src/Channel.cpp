//
// Created by looperX on 2019-07-17.
//

#include <sys/epoll.h>
#include <glog/logging.h>

#include "EventLoop.h"
#include "poll.h"
#include "Channel.h"
/*
 *  EPOLLERR : 文件上发上了一个错误。这个事件是一直监控的，即使没有明确指定
 *  EPOLLNVAL: invalid fd
    EPOLLHUP : 文件被挂断。这个事件是一直监控的，即使没有明确指定
    EPOLLRDHUP : 对端关闭连接或者shutdown写入半连接
    EPOLLET : 开启边缘触发，默认的是水平触发，所以我们并未看到EPOLLLT
    EPOLLONESHOT : 一个事件发生并读取后，文件自动不再监控
    EPOLLIN : 文件可读
    EPOLLPRI : 文件有紧急数据可读
    EPOLLOUT : 文件可写
    EPOLLWAKEUP : 如果EPOLLONESHOT和EPOLLET清除了，并且进程拥有CAP_BLOCK_SUSPEND权限，那么这个标志能够保证事件在挂起或者处理的时候，系统不会挂起或休眠
 *
 * */

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop* loop, int fd)
        : loop_(loop),
          fd_(fd),
          events_(0),
          revents_(0),
          index_(-1)
{
    LOG(INFO) << "start channel";
}

Channel::~Channel()
{
    if (loop_->isInLoopThread())
    {
//        assert(!loop_->hasChannel(this));
            LOG(INFO) << "destructor channel";
    }
}

void Channel::update()
{
//    addedToLoop_ = true;
    loop_->updateChannel(this);
}

//void Channel::handleEvent(Timestamp receiveTime)
void Channel::handleEvent()
{
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        if (closeCallback_) closeCallback_();
    }

    if (revents_ & POLLNVAL)
    {
        LOG(INFO) << "fd = " << fd_ << " Channel::handle_event() EPOLLNVAL";
    }

    if (revents_ & (EPOLLERR | POLLNVAL))
    {
        if (errorCallback_) errorCallback_();
    }
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP))
    {
        if (readCallback_) readCallback_();
    }
    if (revents_ & EPOLLOUT)
    {
        if (writeCallback_) writeCallback_();
    }
}
