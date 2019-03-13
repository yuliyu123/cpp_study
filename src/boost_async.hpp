#ifndef BOOST_ASYNC
#define BOOST_ASYNC

#include "CommonDef.h"

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
	AsioAcceptor acceptor_;
    AsioTcpSocket socket_;
    AsioIoService& io_service_;
    // AsioTcpSolver resolver_;
    short port_;
};

#define BOOST_ASYNC
#endif
