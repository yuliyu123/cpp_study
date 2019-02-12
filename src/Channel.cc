#include "Channel.h"
#include "CommonDef.h"
#include "EventLoop.h"

class EventLoop;
class HttpData;

Channel::Channel(EventLoop* loop)
    : loop_(loop)
    , events_(0)
    , last_events_(0)
{}

Channel::Channel(EventLoop* loop, int fd)
    : loop_(loop)
    , fd_(fd)
    , events_(0)
    , last_events_(0)

{}
Channel::~Channel()
{}

void Channel::handleRead()
{
    if (readCallBack_)
    {
        readCallBack_();
    }
}

void Channel::handleWrite()
{
    if (writeCallback_)
    {
        writeCallback_();
    }
}

void Channel::handleConn()
{
    if (connCallback_)
    {
        connCallback_();
    }
}
