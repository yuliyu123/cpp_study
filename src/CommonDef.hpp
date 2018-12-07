#ifndef COMMONDEF


#include <memory>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <boost/optional.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>

using AsioIoService = boost::asio::io_service;
using AsioEndPoint = boost::asio::ip::tcp::endpoint;
using AsioTcp = boost::asio::ip::tcp;
using AsioTcpSocket = boost::asio::ip::tcp::socket;
using AsioAcceptor = boost::asio::ip::tcp::acceptor;
using AsioIpAddress = boost::asio::ip::address;
using SystemErrorCode = boost::system::error_code;
using AsioTcpAsolver = boost::asio::ip::tcp::resolver;
using boost::asio::ip::tcp;

#define COMMONDEF
#endif
