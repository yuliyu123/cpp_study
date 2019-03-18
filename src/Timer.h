#pragma once

#include <memory>
#include <deque>
#include <queue>
#include <unistd.h>
#include "CommonDef.h"
#include "Channel.h"
#include "HttpData.h"

class Timer
{
public:
	Timer(AsioIoService& ioservice, bool isRepeated);
	Timer(AsioIoService& ioservice, uint64_t count);
	~Timer();

	bool start(uint64_t interval, TimerCallback handler);
	void stop();
	void timeoutCallback(const boost::system::error_code& ec);

private:
	void defer();

private:
	std::unique_ptr<AsioSteadyTimer> timer_;
	// if current timer repeated, if yes, count++
	uint64_t count_ {0};
	bool isRepeated_ {false};
	bool current_ {0};  // if current timer is equal to the latest timer
	TimerCallback cb_;
	int64_t interval_;
};

struct TimerCmp
{
	bool operator()(std::shared_ptr<Timer> &lhs, std::shared_ptr<Timer> &rhs)
	{
		return lhs->getExpTimer() > rhs->getExpTimer();
	}
};

class TimerManager
{
public:
	TimerManager();
	~TimerManager();

	void add_timer(std::shared_ptr<HttpData> httpDataPtr, int timeout);
	void handle_expired_event();

private:
	typedef std::shared_ptr<Timer> timerPtr_;
	std::priority_queue<timerPtr_, std::deque<timerPtr_>, TimerCmp> timerQueue_;
};
