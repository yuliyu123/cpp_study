#ifndef BOOST_ASYNC
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

class boost_async: public std::enable_shared_from_this<boost_async>
{
public:
	explicit boost_async(AsioTcpSocket socket);
	~boost_async() = default;
	 void start();
	 void stop();
	 void asyncRead();
	 void asyncWrite(std::string& msg);


private:
	static constexpr int DATA_SIZE {2048};

	AsioTcpSocket socket_;
    std::atomic_bool close_;
    char data_[DATA_SIZE]{0};
    boost::asio::io_service io_service_;
    AsioAcceptor acceptor_;
};

#define BOOST_ASYNC
#endif
