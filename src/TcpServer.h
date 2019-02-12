//
// Created by loohan on 2019/1/7.
//

#ifndef CPP_STUDY_TCPSERVER_H
#define CPP_STUDY_TCPSERVER_H

#include "CommonDef.h"
#include "Channel.h"
#include "EventLoopThreadPool.h"
#include "Util.h"

class TcpServer : boost::noncopyable
{
public:
    TcpServer(EventLoop *loop, int threadNums, int port);

    void start();
    void newConnection();
    void handleThisConn()
    {
        loop_->addToEpoller(acceptChannelPtr_);
    }

    EventLoop* loop()
    {
        return loop_;
    }

private:
    EventLoop* loop_;
    int threadNums_;
    int port_;
    std::shared_ptr<EventLoopThreadPool> eventLoopPoolPtr_;
    std::shared_ptr<Channel> acceptChannelPtr_;
    int listenFd_;
    bool started_;
    static const int MAXFDS = 10000;
};


#endif //CPP_STUDY_TCPSERVER_H
