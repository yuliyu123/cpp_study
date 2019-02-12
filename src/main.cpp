//
// Created by loohan on 2019/1/7.
//
#include "base/Logging.h"
#include "TcpServer.h"


int main(int argc, char *argv[])
{
    LOG << "start log test in main function";
    int threadNum = 4;
    int port = 80;
    std::string logPath = "./WebServer.log";

    // parse args
    int opt;
    const char *str = "t:l:p:";
    while ((opt = getopt(argc, argv, str))!= -1)
    {
        switch (opt)
        {
            case 't':
            {
                threadNum = atoi(optarg);
                break;
            }
            case 'l':
            {
                logPath = optarg;
                if (logPath.size() < 2 || optarg[0] != '/')
                {
                    printf("logPath should start with \"/\"\n");
                    abort();
                }
                break;
            }
            case 'p':
            {
                port = atoi(optarg);
                break;
            }
            default: break;
        }
    }
//    Logger::setLogFileName(logPath);
    // STL库在多线程上应用
#ifndef _PTHREADS
    LOG << "_PTHREADS is not defined !";
#endif
    std::cout << "init server" << std::endl;
    EventLoop mainLoop;
    std::cout << "init server" << std::endl;
    TcpServer server(&mainLoop, threadNum, port);
    std::cout << "start server" << std::endl;
    server.start();
    mainLoop.loop();

    return 0;
}
