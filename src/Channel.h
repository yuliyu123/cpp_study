#ifndef CHANNEL_H
#define CHANNEL_H

#include "CommonDef.h"
#include "Timer.h"
#include <string>
#include <unordered_map>
#include <memory>
#include <sys/epoll.h>
#include <functional>

class EventLoop;
class HttpData;

// dispatch event
class Channel
{
typedef std::function<void()> EventCallback;

public:
	Channel(EventLoop* loop);
	Channel(EventLoop* loop, int fd);
	~Channel();
	// void remove();
	// void update();

	void setReadCallback(EventCallback&& cb)
	{
		readCallBack_ = std::move(cb);
	}

	void setWriteCallBack(EventCallback&& cb)
	{
		writeCallback_ = std::move(cb);
	}

	void setCloseCallback(EventCallback&& cb)
	{
		closeCallback_ = std::move(cb);
	}

	void setErrorCallback(EventCallback&& cb)
	{
		errorCallback_ = std::move(cb);
	}

	void setConnCallback(EventCallback&& cb)
	{
		connCallback_ = std::move(cb);
	}

	int getFd()
	{
		return fd_;
	}

	void setFd(int fd)
	{
		fd_ = fd;
	}

	void setHolder(std::shared_ptr<HttpData> holder)
	{
		holder_ = holder;
	}

	std::shared_ptr<HttpData> getHolder()
	{
		std::shared_ptr<HttpData> holderPtr(holder_.lock());
		return holderPtr;
	}

	void setEvents(uint32_t events)
	{
		events_ = events;
	}

	// set current event
	void setREvents(uint32_t revents)
	{
		revents_ = revents;
	}

	uint get_last_events()
	{
		return last_events_;
	}

	void handleEvents()
	{
		events_ = 0;

		if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN))
        {
            events_ = 0;
            return;
        }

        if (revents_ & EPOLLERR)
        {
        	if (errorCallback_)
        	{
        		errorCallback_();
        	}
        	revents_ = 0;
        	return;
        }

        if (revents_ & (EPOLLIN | EPOLLHUP | EPOLLPRI))
        {
        	handleRead();
        }

        if (revents_ & EPOLLOUT)
        {
        	handleWrite();
        }

        handleConn();
	}

	bool equalAndUpdateLastEvents()
	{
		bool ret = (last_events_ == events_);
		last_events_ = events_;
		return ret;
	}

	__uint32_t& getEvents()
	{
		return last_events_;
	}

private:
	void handleRead();
	void handleWrite();
	void handleError(int fd, int error_nums, std::string error_msg);
	void handleConn();

	EventLoop* loop_;
	int fd_;
	uint32_t events_;
	uint32_t revents_;
	uint32_t last_events_;

	// 方便找到上层持有该Channel的对象
	std::weak_ptr<HttpData> holder_;

    EventCallback readCallBack_;
    EventCallback writeCallback_;
    EventCallback connCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;
};

typedef std::shared_ptr<Channel> channelPtr;

#endif