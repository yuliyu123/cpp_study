set (base_src
		Thread.cpp
#        CountDownLatch.cpp
		)

add_library(libserver_base STATIC
		${base_src}
		)

include_directories("${PROJECT_SOURCE_DIR}/src")
target_link_libraries(libserver_base pthread rt)

#set_target_properties(libserver_base PROPERTIES OUTPUT_NAME "server_base")
