//
// Created by looperX on 2019-08-20.
//

#ifndef CPP_STUDY_TIMERQUEUE_H
#define CPP_STUDY_TIMERQUEUE_H

#include "EventLoopBase.h"

class timer_queue {
    timer_queue();
    ~timer_queue();

    int add_timer(timer_event& te);
    void del_timer(int timer_id);

    int notifier() const { return _timerfd; }
    int size() const { return _count; }
};


#endif //CPP_STUDY_TIMERQUEUE_H
