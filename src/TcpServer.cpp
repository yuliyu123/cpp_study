//
// Created by loohan on 2019/1/7.
//

#include <functional>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "TcpServer.h"

TcpServer::TcpServer(EventLoop *loop, int threadNums, int port)
    : loop_(loop)
    , threadNums_(threadNums)
    , port_(port)
    , eventLoopPoolPtr_(new EventLoopThreadPool(loop_, threadNums_))
    , acceptChannelPtr_(new Channel(loop_))
    , listenFd_(socket_bind_listen(port))
    , started_(false)
{
    acceptChannelPtr_->setFd(listenFd_);
    std::cout << listenFd_ << std::endl;
    handle_for_sigpipe();
    // 设为非阻塞模式
    if (setSocketNonBlocking(listenFd_) < 0)
    {
        perror("set socket non block failed");
        abort();
    }
}

void TcpServer::start()
{
    std::cout << "enter start server" << std::endl;
    eventLoopPoolPtr_->start();
    acceptChannelPtr_->setEvents(EPOLLIN | EPOLLET);
    acceptChannelPtr_->setReadCallback(std::bind(&TcpServer::newConnection,this));
    acceptChannelPtr_->setConnCallback(std::bind(&TcpServer::handleThisConn, this));
    loop_->addToEpoller(acceptChannelPtr_);
    started_ = true;
}

void TcpServer::newConnection()
{
    printf("enter newConnection");
    struct sockaddr_in client_addr;

    memset(&client_addr, 0, sizeof(struct sockaddr_in));
    socklen_t client_addr_len = sizeof(client_addr);
    int accept_fd = 0;

    while ((accept_fd = accept(listenFd_, (struct sockaddr*)&client_addr, &client_addr_len)) > 0)
    {
        EventLoop* loop = eventLoopPoolPtr_->getNextLoop();
//        LOG << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port);

        printf("New connection from ");
        if (accept_fd > MAXFDS)
        {
            close(accept_fd);
            continue;
        }

        // set to nonblock mode
        if (setSocketNonBlocking(accept_fd) < 0)
        {
            printf("error here");
            perror("Set non block failed!");
            return;
        }

        setSocketNodelay(accept_fd);

        std::shared_ptr<HttpData> req_info(new HttpData(loop, accept_fd));
        req_info->getChannel()->setHolder(req_info);
        loop->queueInloop(std::bind(&HttpData::newEvent, req_info));
    }
    // set to edge trigger
    acceptChannelPtr_->setEvents(EPOLLIN | EPOLLET);
}



