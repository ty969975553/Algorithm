cmake_minimum_required(VERSION 3.20)

project(algorithm)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE(test queue/benchmark_function.h queue/spscqueue.h queue/test.cc)

ADD_EXECUTABLE(atomic_test queue/test2.cc)

ADD_EXECUTABLE(josephus_test classic/Josephus.cpp)