#include <algorithm>
#include <signal.h>
#include <unistd.h>
#include "Util.h"
#include "EventLoop.h"

__thread EventLoop* t_loopInCurrentThread = 0;

int createEventfd()
{
	int evtfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
	if (evtfd < 0)
	{
		LOG(WARNING) << "Failed in eventfd, will abort";
		abort();
	}
	return evtfd;
}

EventLoop::EventLoop()
	: looping_(false)
	, epoller_(new Epoll)
	, wakeupFd_(createEventfd())
	, quit_(false)
	, eventHandling_(false)
	, callPendingFunctors_(true)
	, threadId_(std::this_thread::get_id())
	, wakupChan_(new Channel(this, wakeupFd_))
{
	if (t_loopInCurrentThread)
	{
		// another event is in this thread
	}
	else
	{
		t_loopInCurrentThread = this;
	}
}

EventLoop::~EventLoop()
{
	close(wakeupFd_);
	t_loopInCurrentThread = NULL;
}

bool EventLoop::isInLoopThread()
{
	return threadId_ == std::this_thread::get_id();
}

bool EventLoop::assertInLoopThread()
{
	assert(isInLoopThread());
}

// event loop
void EventLoop::loop()
{
    LOG(INFO) << "start thread, and entry event loop";
    assert(!looping_);
    assertInLoopThread(); // 处在该线程中， 但该eventloop的loop还没用到
    looping_ = true;
    // this eventloop start loop
    quit_ = false;

    std::vector<channelPtr> channels;

    while (!quit_)
	{
		channels.clear();
		eventHandling_ = true;
		LOG(INFO) << "enter epoller_->polls()";
		channels = epoller_->polls();

		LOG(INFO) << "start handle channels";
		for (auto &it : channels)
        {
            it->handleEvents();
        }
        eventHandling_ = false;
        handlePendingFunctors();
        epoller_->handle_expired_event();
    }
    looping_ = false; // 处理完毕标志false
    // this eventloop finish loop
}

// running event
void EventLoop::runInLoop(Functor&& cb)
{
	if (isInLoopThread())
	{
		cb();
	}
	else
	{
		queueInloop(std::move(cb));
	}
}

void EventLoop::queueInloop(Functor&& cb)
{
	{
		MutexLockGuard lock(mutexLock_);
		pendingFunctors_.push_back(cb);
	}

	if (!isInLoopThread() || callPendingFunctors_)
//		LOG(WARNING) << "wake up one ";
		wakeup();
}

void EventLoop::quit()
{
	quit_ = true;

	//
	if (!assertInLoopThread())
	{
		wakeup();
	}
}

void EventLoop::handlePendingFunctors()
{
    std::vector<Functor> functors;
    callPendingFunctors_ = true;

    // 多线程加锁
    {
        MutexLockGuard lock(mutexLock_);
        functors.swap(pendingFunctors_);
    }

    for (auto functor : functors)
    {
        functor();
    }
    callPendingFunctors_ = false;
}

void EventLoop::wakeup()
{
	int one = 1;
	ssize_t n = writen(wakeupFd_, (char*)(&one), sizeof(one));
	LOG(INFO) << "EventLoop::wakeup() write 8 byte";

	if (n != 1)
	{
		LOG(WARNING) << "EventLoop::wakeup() write " << n << " bytes instead of 8";
	}
}

void EventLoop::handleRead()
{
	int one = 1;
	ssize_t n = readn(wakeupFd_, &one, sizeof(one));

	if (n != 1)
	{
//		LOG << "EventLoop::handleRead() read " << n << " bytes instead of 8";
	}
	// read in and edge trigger, it faster than level trigger
	wakupChan_->setEvents(EPOLLIN | EPOLLET);
}

void EventLoop::handleConn()
{
	updateEpoll(wakupChan_);
}

void EventLoop::shutdown(std::shared_ptr<Channel> chanPtr)
{
	shutDownWR(chanPtr->getFd());
}

