//
// Created by looperX on 2019-07-17.
//

#include <unistd.h>
#include <cstdint> // include this header for uint64_t
#include <assert.h>
#include <errno.h>
#include <poll.h>
#include <sys/epoll.h>
#include <stdint.h>

#include <glog/logging.h>

#include "EventLoop.h"
#include "Epoll.h"

// On Linux, the constants of poll(2) and epoll(4)
// are expected to be the same.
static_assert(EPOLLIN == POLLIN,        "epoll uses same flag values as poll");
static_assert(EPOLLPRI == POLLPRI,      "epoll uses same flag values as poll");
static_assert(EPOLLOUT == POLLOUT,      "epoll uses same flag values as poll");
static_assert(EPOLLRDHUP == POLLRDHUP,  "epoll uses same flag values as poll");
static_assert(EPOLLERR == POLLERR,      "epoll uses same flag values as poll");
static_assert(EPOLLHUP == POLLHUP,      "epoll uses same flag values as poll");

Epoll::Epoll(EventLoop* loop)
//        : Poller(loop),
          : epollfd_(::epoll_create1(EPOLL_CLOEXEC)),
          events_(kInitEventListSize)
{
    if (epollfd_ < 0)
    {
        LOG(INFO) << "EPollPoller::EPollPoller";
    }
}

Epoll::~Epoll()
{
    ::close(epollfd_);
}

// 核心功能，获取当前的活动IO事件填充activeChannels中
void Epoll::poll(int timeoutMs, ChannelList* activeChannels)
{
    LOG(INFO) << "fd total count " << channels_.size();
    // 新事件的到来
    int numEvents = ::epoll_wait(epollfd_,
                                 &*events_.begin(),
                                 static_cast<int>(events_.size()),
                                 timeoutMs);
    int savedErrno = errno;
//    Timestamp now(Timestamp::now());
    if (numEvents > 0)
    {
        LOG(INFO) << numEvents << " events happened";
        fillActiveChannels(numEvents, activeChannels);
//        if (implicit_cast<size_t>(numEvents) == events_.size())
//        {
//            events_.resize(events_.size()*2);
//        }
    }
    else if (numEvents == 0)
    {
        LOG(INFO) << "nothing happened";
    }
    else
    {
        // error happens, log uncommon ones
        if (savedErrno != EINTR)
        {
            errno = savedErrno;
            LOG(ERROR) << "EPollPoller::poll() has error happened";
        }
    }
//    return now;
}

void Epoll::update(int operation, int fd)
{
    struct epoll_event event;
    memset(&event, 0, sizeof event);
//    event.events = channel->events();
    event.data.fd = fd;

    if (::epoll_ctl(epollfd_, operation, fd, &event) < 0)
    {
        if (operation == EPOLL_CTL_MOD)
        {
            LOG(INFO) << "epoll_ctl op = EPOLL_CTL_MOD and  fd = " << fd;
        }
        else if (operation == EPOLL_CTL_MOD)
        {
            LOG(INFO) << "epoll_ctl op = EPOLL_CTL_MOD and  fd = " << fd;
        }
        else
        {
            LOG(INFO) << "epoll_ctl op = EPOLL_CTL_DEL and  fd = " << fd;
        }
    }
}

// 找到活跃的fd，每个fd对应一个channel,设置为当前活跃的fd,set_revents()
void Epoll::fillActiveChannels(int numEvents,
                                     ChannelList* activeChannels) const
{
//    assert(implicit_cast<size_t>(numEvents) <= events_.size());
    for (int i = 0; i < numEvents; ++i)
    {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        // 获取有事件产生的描述符
        int fd = events_[i].data.fd;

        // 获取有事件产生的描述符
        channel->set_revents(events_[i].events); // 设置当前活跃事件到channel中
        activeChannels->push_back(channel);
    }
}

void Epoll::updateChannel(Channel *channel)
{

}
