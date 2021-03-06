//
// Created by looperX on 2019-08-20.
//

#ifndef CPP_STUDY_EVENTLOOPBASE_H
#define CPP_STUDY_EVENTLOOPBASE_H

#include <stdint.h>
#include <stdio.h>//NULL

class EventLoop;

typedef void io_callback(EventLoop* loop, int fd, void *args);//IO事件回调函数
typedef void timer_callback(EventLoop* loop, void* usr_data);//Timer事件回调函数

//让当前loop在一次poll循环后执行指定任务
typedef void (*pendingFunc)(EventLoop*, void *);

struct io_event//注册的IO事件
{
    io_event(): read_cb(NULL), write_cb(NULL), rcb_args(NULL), wcb_args(NULL) { }
    int mask;               //EPOLLIN EPOLLOUT
    io_callback* read_cb;  //callback when EPOLLIN comming
    io_callback* write_cb; //callback when EPOLLOUT comming
    void* rcb_args;   //extra arguments for read_cb
    void* wcb_args;  //extra arguments for write_cb
};

struct timer_event//注册的Timer事件
{
    timer_event(timer_callback* timo_cb, void* data, uint64_t arg_ts, uint32_t arg_int = 0):
            cb(timo_cb), cb_data(data), ts(arg_ts), interval(arg_int)
    {
    }

    timer_callback* cb;
    void* cb_data;
    uint64_t ts;
    uint32_t interval;//interval millis
    int timer_id;
};

#endif //CPP_STUDY_EVENTLOOPBASE_H
