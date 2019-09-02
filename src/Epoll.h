//
// Created by looperX on 2019-07-17.
//

#ifndef CPP_STUDY_EPOLL_H
#define CPP_STUDY_EPOLL_H

#include <vector>
#include <map>

#include "Channel.h"

class Channel;
class EventLoop;

class Epoll {
public:
    typedef std::vector<Channel*> ChannelList;

    Epoll(EventLoop* loop);
    ~Epoll();

//    Timestamp poll(int timeoutMs, ChannelList* activeChannels);
    void poll(int timeoutMs, ChannelList* activeChannels);
    void updateChannel(Channel* channel);

protected:
    typedef std::map<int, Channel*> ChannelMap;
    ChannelMap channels_;

private:
    static const int kInitEventListSize = 16;
    void fillActiveChannels(int numEvents,
                            ChannelList* activeChannels) const;
    void update(int operation, int fd);  // epoll_ctl更改fd状态


    typedef std::vector<struct epoll_event> EventList;
    int epollfd_;
    EventList events_;
};


#endif //CPP_STUDY_EPOLL_H
