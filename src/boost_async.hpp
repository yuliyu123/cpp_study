#ifndef BOOST_ASYNC
#include "CommonDef.hpp"

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
    // boost::asio::io_service io_service_;
    // AsioAcceptor acceptor_;
};

class Service
{
public:
    explicit Service(boost::asio::io_service& io_service, short port);
    void doAccept();
    void startServer();
    void startClient();
	~Service() = default;

private:
	tcp::acceptor acceptor_;
    tcp::socket socket_;
    boost::asio::io_service& io_service_;
    AsioTcpAsolver resolver_;
    short port_;
};

#define BOOST_ASYNC
#endif
