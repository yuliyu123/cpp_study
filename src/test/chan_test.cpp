//
// Created by looperX on 2019-08-05.
//
#include <sys/timerfd.h>
#include <stdio.h>
#include <strings.h>

#include "Channel.h"
#include "EventLoop.h"

EventLoop* g_loop;

void timeOut()
{
    printf("timeOut/n");
//    loop->quit();
    g_loop->quit();
}

int main()
{
    EventLoop loop;
    g_loop = &loop;

    int timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    Channel channel(&loop, timerfd);
    channel.setReadCallback(timeOut);
    channel.enableReading();

    struct itimerspec howlong;
    bzero(&howlong, sizeof(howlong));

    howlong.it_value.tv_sec = 5;
    timerfd_settime(timerfd, 0, &howlong, NULL);

    loop.loop();
}

