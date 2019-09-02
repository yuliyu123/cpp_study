add_executable(chan_test chan_test.cpp)
target_link_libraries(chan_test WebServer)

add_executable(eventloop_test eventloop_test.cpp)
target_link_libraries(eventloop_test WebServer)
