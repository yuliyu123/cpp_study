#include "Epoll.h"
#include <sys/epoll.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <queue>
#include <deque>
#include <assert.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

const int EVENTSNUM = 4096;
const int EPOLLWAIT_TIME = 10000;

Epoll::Epoll()
    : epollFd_(epoll_create1(EPOLL_CLOEXEC))
    , epoll_events_(10)
{
    assert(epollFd_ > 0);
}

Epoll::~Epoll()
{ }

void Epoll::epoll_add(channelPtr request, int timeout)
{
    int fd = request->getFd();
    if (timeout > 0)
    {
        add_timer(request, timeout);
        httpdDatas_[fd] = request->getHolder();
    }

    struct epoll_event event;
    event.data.fd = fd;
    event.events = request->getEvents();


    request->equalAndUpdateLastEvents();

    chans_[fd] = request;
    if (epoll_ctl(epollFd_, EPOLL_CTL_ADD, fd, &event) < 0)
    {
        perror("epoll_add error");
        chans_[fd].reset();
    }
}

void Epoll::epoll_mod(channelPtr request, int timeout)
{
    if (timeout > 0)
    {
        add_timer(request, timeout);
    }

    int fd = request->getFd();

    if (!request->equalAndUpdateLastEvents())
    {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = request->getEvents();
        if (epoll_ctl(epollFd_, EPOLL_CTL_MOD, fd, &event) < 0)
        {
            perror("epoll_mod error");
            chans_[fd].reset();
        }
    }
}

void Epoll::epoll_del(channelPtr request)
{
    int fd = request->getFd();
    struct epoll_event event;
    event.data.fd = fd;
    event.events = request->getEvents();

    if (epoll_ctl(epollFd_, EPOLL_CTL_DEL, fd, &event) < 0)
    {
        perror("epoll_del error");
    }

    chans_[fd].reset();
    httpdDatas_[fd].reset();
}

void Epoll::add_timer(channelPtr request, int timeout)
{
    std::shared_ptr<HttpData> httpDataPtr = request->getHolder();

    if (httpDataPtr)
    {
        timeManager_.add_timer(httpDataPtr, timeout);
    }
    else 
    {
        perror("timeManager add timer error");
    }

}

// 返回活跃事件数目
std::vector<channelPtr> Epoll::polls()
{
    while (true)
    {
        std::cout << epoll_events_.size() << std::endl;
        int event_count = epoll_wait(epollFd_, &*epoll_events_.begin(), epoll_events_.size(), EPOLLWAIT_TIME);
        if (event_count < 0)
        {
            perror("error, epoll wait fail");
        }
        std::cout << "enter req datas" << std::endl;
        std::vector<channelPtr> req_datas = get_events_request(event_count);
        if (req_datas.size() > 0)
        {
            return req_datas;
        }
    }
}

// dispatch events to handle, invoke channel to handle event to read/write
std::vector<channelPtr> Epoll::get_events_request(int epoll_nums)
{
     std::vector<channelPtr> req_datas;

     for (int i = 0; i < epoll_nums; ++i)
     {
        // get fd
        int fd = epoll_events_[i].data.fd;
        channelPtr cur_req = chans_[fd];
        
        if (cur_req)
        {
            cur_req->setREvents(epoll_events_[i].events);
            cur_req->setEvents(0);
            req_datas.push_back(cur_req);
        }
        else
        {
            perror("has no current event need to handle");
        }
     }

     return req_datas;
}

void Epoll::handle_expired_event()
{
    timeManager_.handle_expired_event();
}
