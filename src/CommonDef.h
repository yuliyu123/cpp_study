#ifndef COMMONDEF_H
#define COMMONDEF_H

#include <sys/epoll.h>
#include <sys/time.h>

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <cstring>
#include <chrono>
#include <assert.h>

#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/optional.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/system/error_code.hpp>
#include <glog/logging.h>

using namespace std;
using namespace chrono;
using AsioIoService = boost::asio::io_service;
using AsioEndPoint = boost::asio::ip::tcp::endpoint;
using AsioTcp = boost::asio::ip::tcp;
using AsioTcpSocket = boost::asio::ip::tcp::socket;
using AsioAcceptor = boost::asio::ip::tcp::acceptor;
using AsioIpAddress = boost::asio::ip::address;
//using SystemErrorCode = boost::system::error_code;
using AsioSteadyTimer = boost::asio::steady_timer;
using TimerCallback = std::function<void()>;


#define COMMONDEF
#endif
