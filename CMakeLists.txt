cmake_minimum_required(VERSION 2.8)
project(cpp_study)

#google test/mock
#include_directories(PUBLIC SYSTEM 3rdlib/gtest)
#add_library(3rdlib/gtest STATIC 3rdlib/gtest/gmock-gtest-all.cc)
#add_library(3rdlib/gtest STATIC 3rdlib/gtest/gmock-gtest-all.cc)
#add_library(3rdlib/gtest STATIC 3rdlib/gtest/gmock-gtest-all.cc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lboost_system -lglog -lgflags ")

SET(CMAKE_BUILD_TYPE "Debug")
#SET(CMAKE_BUILD_TYPE "Release")

# option(BUILD_TESTS "Include test targets" ON)
# message(STATUS "Include test targets: ${BUILD_TESTS}")

find_package(Boost COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
endif()

find_package (Glog REQUIRED)
if(glog_FOUND)
    message(STATUS "glog has founded: ${glog_INCLUDE_DIRS}")
    message(STATUS "glog_VERSION: ${glog_VERSION}")
endif()

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
add_definitions(-DBOOST_SYSTEM_NO_DEPRECATED)

add_subdirectory(src)
add_subdirectory(src/base)
#add_subdirectory(src/networkif)

include_directories("${PROJECT_SOURCE_DIR}/3rdlib")
include_directories("${PROJECT_SOURCE_DIR}/src")

# open ut test
# if(BUILD_TESTS)
#     enable_testing()
# 	add_subdirectory(test)
# endif(BUILD_TESTS)
