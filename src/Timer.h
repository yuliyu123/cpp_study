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
	Timer(std::shared_ptr<HttpData> requestData, int timeout);
	Timer(Timer& rhs);
	~Timer();

	void update(int timeout);
	bool isvalid();
	void clearReq();
	void setDeleted();
	bool isDeleted() const;
	size_t getExpTimer() const;

private:
	bool deleted_;
	size_t expriedTime_;
	std::shared_ptr<HttpData> httpDataPtr_;
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
