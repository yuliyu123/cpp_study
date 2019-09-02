//
// Created by looperX on 2019-08-14.
//
#include <iostream>
#include <thread>

#include "EventLoop.h"

EventLoop* g_loop;

void threadFunc()
{
    g_loop->loop();
}

int main()
{
    EventLoop loop;
    g_loop = &loop;
    std::thread t1(threadFunc);
    t1.join();
}

