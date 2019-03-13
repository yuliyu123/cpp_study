#pragma once

#include <iostream>
#include <memory>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <linux/unistd.h>
#include <stdint.h>
#include <assert.h>
#include <signal.h>

#include "CommonDef.h"
#include "CurrentThread.h"
#include "CountDownLatch.h"

class Thread : boost::noncopyable
{
public:
    typedef std::function<void()> ThreadFunc;
    explicit Thread(const ThreadFunc& threadFunc, const std::string& name);
    ~Thread();
    void start();
    int join();
    bool started()
    {
        return started_;
    }
    pid_t tid() { return tid_; }
    const std::string& name()
    {
        return name_;
    }

private:
    void setDefaultName();
    bool started_;
    bool joined_;
    pthread_t pthread_id_;
    pid_t tid_;
    ThreadFunc threadFunc_;
    std::string name_;
    CountDownLatch latch_;
};


