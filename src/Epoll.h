#pragma once

#include "CommonDef.h"
#include "Timer.h"
#include "HttpData.h"
#include "Channel.h"

class Epoll
{
public:
    Epoll();
    ~Epoll();
    void epoll_add(channelPtr request, int timeout);
    void epoll_mod(channelPtr request, int timeout);
    void epoll_del(channelPtr request);

    void add_timer(channelPtr request, int timeout);

    // return active events
    int getEventFds()
    {
        return epollFd_;
    }

    void handle_expired_event();
    std::vector<std::shared_ptr<Channel>> polls();

    std::vector<std::shared_ptr<Channel>> get_events_request(int epoll_nums);
private:
    static const int MAXFDS = 100000;
    int epollFd_;
    std::vector<epoll_event> epoll_events_;
    std::shared_ptr<Channel> chans_[MAXFDS];
    std::shared_ptr<HttpData> httpdDatas_[MAXFDS];
    TimerManager timeManager_;
//    Timer timer_;
};
