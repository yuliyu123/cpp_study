//
// Created by looperX on 2019-07-25.
//

#ifndef CPP_STUDY_SOCKETOPS_H
#define CPP_STUDY_SOCKETOPS_H

#include <fcntl.h>
#include <stdio.h>  // snprintf
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/eventfd.h>

#include <glog/logging.h>

// 创建socket并且bind
int createAndbind (int port) {
    int sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sfd == -1) {
        return -1;
    }
    struct sockaddr_in sa;
    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port   = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sfd, (struct sockaddr*)&sa, sizeof(struct sockaddr)) == -1) {
        return -1;
    }
    return sfd;
}


// 设置成非阻塞模式
int SetNonBlocking (int fd) {
    int flags = fcntl (fd, F_GETFL, 0);
    if (flags == -1) {
        return -1;
    }
    if(fcntl (fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        return -1;
    }
    return 0;
}

/*
 * https://blog.csdn.net/majianfei1023/article/details/51199702
 * 设置成EFD_NONBLOCK 非阻塞模式
 * EFD_CLOEXEC：顾名思义是在执行 exec() 调用时关闭文件描述符，防止文件描述符泄漏给子进程。
 *
 * */

int createEventfd()
{
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if (evtfd < 0)
    {
        LOG(INFO) << "Failed in eventfd";
        abort();
    }
    return evtfd;
}

ssize_t write(int sockfd, const void *buf, size_t count)
{
    return ::write(sockfd, buf, count);
}


#endif //CPP_STUDY_SOCKETOPS_H
