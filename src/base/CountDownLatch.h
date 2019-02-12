//
// Created by looperX on 2019-02-12.
//

#ifndef CPP_STUDY_COUNTDOWNLATCH_H
#define CPP_STUDY_COUNTDOWNLATCH_H

#include "CommonDef.h"
#include "MutexLock.h"
#include "Condition.h"

class CountDownLatch
{
public:
    explicit CountDownLatch(int count);
    void wait();
    void countDown();

private:
    mutable MutexLock mutex_;
    Condition condition_;
    int count_;
};


#endif //CPP_STUDY_COUNTDOWNLATCH_H
