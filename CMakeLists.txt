cmake_minimum_required(VERSION 2.8)
project(cpp_study)

#google test/mock
include_directories(PUBLIC SYSTEM gtest)
add_library(gtest STATIC gtest/gmock-gtest-all.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lboost_system")

# option(BUILD_TESTS "Include test targets" ON)
# message(STATUS "Include test targets: ${BUILD_TESTS}")

#find_package(Boost 1.53.0 COMPONENTS system filesystem REQUIRED)
find_package(Boost 1.65.0 COMPONENTS system thread filesystem REQUIRED)
if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})

endif()

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
add_definitions(-DBOOST_SYSTEM_NO_DEPRECATED)

add_subdirectory(src)
add_subdirectory(src/base)
#add_subdirectory(src/networkif)

include_directories("${PROJECT_SOURCE_DIR}/src")


# target_link_libraries( src)

# open ut test
# if(BUILD_TESTS)
#     enable_testing()
# 	add_subdirectory(test)
# endif(BUILD_TESTS)
