#ifndef EVENTLOOP
#define EVENTLOOP

#include "CommonDef.h"
#include <vector>
#include "base/MutexLock.h"
#include "Channel.h"
#include "Epoll.h"
#include "Util.h"

class EventLoop
{
public:
	typedef std::function<void()> Functor;
	EventLoop();
	~EventLoop();

	bool isInLoopThread();
	bool assertInLoopThread();

	void runInLoop(Functor&& cb);
	void queueInloop(Functor&& cb);

	void addToEpoller(std::shared_ptr<Channel> chanPtr, int timeout = 0)
	{
		epoller_->epoll_add(chanPtr, 0);
	}

	void updateEpoll(std::shared_ptr<Channel> chanPtr, int timeout = 0)
	{
		epoller_->epoll_mod(chanPtr, 0);
	}

	void removeFromPoller(std::shared_ptr<Channel> chanPtr)
	{
		epoller_->epoll_del(chanPtr);
	}

	void shutdown(std::shared_ptr<Channel> chanPtr);

	void loop();
    void quit();


private:
	void wakeup();
	void handleRead();
	void handleConn();
	void handlePendingFunctors();

	bool looping_;
	std::shared_ptr<Epoll> epoller_;

	bool eventHandling_;
	MutexLock mutexLock_;
	std::vector<Functor> pendingFunctors_;
	bool callPendingFunctors_;
	int wakeupFd_;
	bool quit_;
	const std::thread::id threadId_;
//	const pid_t threadId_;
	std::shared_ptr<Channel> wakupChan_;
};

#endif
