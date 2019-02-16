//
// Created by loohan on 2019/1/7.
//
#include "TcpServer.h"

void initGlog()
{
    FLAGS_colorlogtostderr = true; //设置输出到屏幕的日志显示相应颜色
    google::SetLogDestination(google::GLOG_FATAL, "./log/log_"); // 设置 google::FATAL 级别的日志存储路径和文件名前缀
    google::SetLogDestination(google::GLOG_ERROR, "./log/log_"); //设置 google::ERROR 级别的日志存储路径和文件名前缀
    google::SetLogDestination(google::GLOG_WARNING, "./log/log_"); //设置 google::WARNING 级别的日志存储路径和文件名前缀
    google::SetLogDestination(google::GLOG_INFO, "./log/log_"); //设置 google::INFO 级别的日志存储路径和文件名前缀
    FLAGS_logbufsecs = 0; //缓冲日志输出，默认为30秒，此处改为立即输出
    FLAGS_max_log_size = 100; //最大日志大小为 100MB
    FLAGS_stop_logging_if_full_disk = true; //当磁盘被写满时，停止日志输出
}

int main(int argc, char *argv[])
{
    int threadNum = 4;
    int port = 80;
    google::InitGoogleLogging(argv[0]);  // 初始化 glog
//    google::ParseCommandLineFlags(&argc, &argv, true);  // 初始化 gflags

    initGlog();
    // parse args
    int opt;
    const char *str = "t:p:";
    while ((opt = getopt(argc, argv, str))!= -1)
    {
        switch (opt)
        {
            case 't':
            {
                threadNum = atoi(optarg);
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
    // STL库在多线程上应用
#ifndef _PTHREADS
    LOG(INFO) << "_PTHREADS is not defined !";
#endif
    EventLoop mainLoop;
    TcpServer server(&mainLoop, threadNum, port);
    server.start();
    mainLoop.loop();

    return 0;
}
