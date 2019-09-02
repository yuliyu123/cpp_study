set (server_src
        timer_queue.cpp
        thread_pool.cpp
        EventLoopBase.h
        EventLoop.cpp
        Channel.cpp
        Epoll.cpp
        #        EventLoopThread.cc
        #        EventLoopThreadPool.cc
        #        HttpData.cc
        #        TcpServer.cpp
        #        ThreadPool.cc
        #        Timer.cc
        main.cpp
        #        Util.cpp
        )

include_directories("${PROJECT_SOURCE_DIR}/src")

#add_executable(WebServer ${server_src})
add_library(WebServer ${server_src})
target_link_libraries(WebServer libserver_base glog::glog)
install(TARGETS WebServer DESTINATION lib)
#target_link_libraries(WebServer glog::glog)
add_subdirectory(test/)
