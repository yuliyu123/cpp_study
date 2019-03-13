//
// Created by looperX on 2019-02-12.
//

#include "CountDownLatch.h"

CountDownLatch::CountDownLatch(int count)
        : mutex_(),
          condition_(mutex_),
          count_(count)
{ }

void CountDownLatch::wait()
{
    MutexLockGuard lock(mutex_);
    while (count_ > 0)
        condition_.wait();
}

void CountDownLatch::countDown()
{
    MutexLockGuard lock(mutex_);
    --count_;
    LOG(INFO) << "count is: " << count_;
    if (count_ == 0)
        LOG(WARNING) << "count is 0, will notify all thread";
        condition_.notifyAll();
}
