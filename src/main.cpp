//
// Created by looperX on 2019-07-17.
//

#include <glog/logging.h>
#include <vector>

using namespace std;


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

int main()
{

}