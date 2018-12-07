#include "boost_async.hpp"

using boost::asio::ip::tcp;

boost_async::boost_async(AsioTcpSocket socket)
    : socket_(std::move(socket))
{
}

void boost_async::start()
{
	std::string msg = "hello,world";
    asyncWrite(msg);
}

void boost_async::stop()
{
    socket_.close();
}

void boost_async::asyncRead()
{
	auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_),  // 异步读
            [this, self](const boost::system::error_code &ec, size_t bytesTransferred)  // 读操作完成时回调该函数
            {  // 捕获`self`使shared_ptr<session>的引用计数增加1，在该例中避免了async_read()退出时其引用计数变为0
                if (!ec)
                {
                    printf("%s\n", "read complate, there has no error");
                }
                printf("%s\n", "read complate, there has error, please check it");
            });

}

void boost_async::asyncWrite(std::string& msg)
{
    std::vector<char> datas;
    copy(msg.begin(), msg.end(), back_inserter(datas));

    boost::asio::async_write(socket_, boost::asio::buffer(datas, msg.length()),
    	[this](const boost::system::error_code& ec, size_t size)
    	{
            if (!ec)
            {
            	printf("%s\n", "write into buff successfully");
            }
    	});
}

Service::Service(boost::asio::io_service& io_service, short port)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
     , socket_(io_service)
     , io_service_(io_service)
     , resolver_(io_service)
     , port_(port)
{}

void Service::startServer()
{
    doAccept();
    io_service_.run();
}

void Service::startClient()
{
    socket_.async_connect(tcp::endpoint(tcp::v4(), port_),
       [this](boost::system::error_code ec)
       {
            if (!ec)
            {
                std::make_shared<boost_async>(std::move(socket_))->asyncRead();
            }
       }
    );
    io_service_.run();
}

void Service::doAccept()
{
	acceptor_.async_accept(socket_,
		[this](boost::system::error_code ec)
		{
			if (!ec)
			{
				std::make_shared<boost_async>(std::move(socket_))->start();
				return;
			}
		});
}
