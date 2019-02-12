#include "Timer.h"

Timer::Timer(std::shared_ptr<HttpData> requestData, int timeout)
    : deleted_(false)
    , httpDataPtr_(requestData)
{
    struct timeval now;
    gettimeofday(&now, NULL);

    // 以毫秒计算
    expriedTime_ = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}


Timer::Timer(Timer &rhs)
    : httpDataPtr_(rhs.httpDataPtr_)
{
}

Timer::~Timer()
{
    if (httpDataPtr_)
    {
        httpDataPtr_->handleClose();
    }
}

// update timer val
void Timer::update(int timeout)
{
    struct timeval now;
    gettimeofday(&now, NULL);
    expriedTime_ = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

bool Timer::isvalid()
{
    struct timeval now;
    gettimeofday(&now, NULL);
    size_t tmp= (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000));

    if (tmp < expriedTime_)
    {
        return true;
    }
    this->setDeleted();
    return false;
}

void Timer::clearReq()
{
    httpDataPtr_.reset();
    this->setDeleted();

}

void Timer::setDeleted()
{
    deleted_ = true;
}

bool Timer::isDeleted() const {
    return true;
}

size_t Timer::getExpTimer() const
{
    return expriedTime_;
}

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
