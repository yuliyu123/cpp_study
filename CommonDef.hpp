#ifndef COMMONDEF
#include <memory>
#include <string>
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

#define COMMONDEF
#endif