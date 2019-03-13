#ifndef TIMER_H
#define TIMER_H

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

class HttpData;
class TimerManager
{
public:
	TimerManager();
	~TimerManager();

	void add_timer(std::shared_ptr<HttpData> httpDataPtr, int timeout);
	void handle_expired_event();
};


#endif
