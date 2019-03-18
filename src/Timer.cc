#include "Timer.h"

TimerManager::TimerManager() {

}

TimerManager::~TimerManager() {

}

void TimerManager::add_timer(std::shared_ptr<HttpData> httpDataPtr, int timeout)
{
    timerPtr_ newTimer(new Timer(httpDataPtr, timeout));
    timerQueue_.push(newTimer);
    httpDataPtr->linkTimer(newTimer);
}

void TimerManager::handle_expired_event()
{
    while (!timerQueue_.empty())
    {
        timerPtr_ nowTimer = timerQueue_.top();
        if (nowTimer->isDeleted()) timerQueue_.pop();

        else if (nowTimer->isvalid() != true) timerQueue_.pop();

        else
            break;
    }
}
