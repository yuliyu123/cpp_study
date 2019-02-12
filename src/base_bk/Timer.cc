#include "Timer.h"

// namespace asyncServer
// {
// namespace base
// {

Timer::Timer(AsioIoService& ioservice, bool isRepeated)
	: timer_(new AsioSteadyTimer(ioservice))
	, count_(0)
	, isRepeated_(isRepeated)
{

}

Timer::Timer(AsioIoService& ioservice, uint64_t count)
	: timer_(new AsioSteadyTimer(ioservice))
	, count_(count)
	, isRepeated_(count > 0 ?  true : false)
{

}

bool Timer::start(uint64_t interval, TimerCallback handler)
{
	cb_ = handler;
	interval_ = interval;
	current_++;

    if (timer_->expires_from_now(std::chrono::milliseconds(interval_)) > 0)
    {
    	return false;
    }

	timer_->async_wait(boost::bind(&Timer::timeoutCallback, this,
		boost::asio::placeholders::error));
}

void Timer::defer()
{
	if (timer_->expires_from_now(std::chrono::milliseconds(interval_)) == 0)
	{
		return;
	}

	timer_->async_wait(boost::bind(&Timer::timeoutCallback, this,
		boost::asio::placeholders::error));
}

void Timer::timeoutCallback(const boost::system::error_code& ec)
{
	if (ec == boost::asio::error::operation_aborted)
	{
		return;
	}

	if (isRepeated_)
	{
		if (count_)
		{
			current_++;
		}

	    timer_->expires_from_now(std::chrono::milliseconds(interval_));
		timer_->async_wait(boost::bind(&Timer::timeoutCallback, this,
			boost::asio::placeholders::error));
	}

	if ((count_ > 0) && (count_ == current_))
	{
		stop();
	}

	if (cb_)
	{
		cb_();
	}
}

void Timer::stop()
{
	boost::system::error_code ec;
	timer_->cancel();
	cb_ = nullptr;
}


