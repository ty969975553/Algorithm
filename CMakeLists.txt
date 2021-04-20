cmake_minimum_required(VERSION 3.20)

project(algorithm)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

ADD_EXECUTABLE(test util/benchmark_function.h queue/spscqueue.h queue/test.cc)

ADD_EXECUTABLE(atomic_test queue/test2.cc)

ADD_EXECUTABLE(josephus_test classic/Josephus.cpp)

ADD_EXECUTABLE(bitset_test classic/bitset.cpp)

ADD_EXECUTABLE(find_test classic/find_and_replace.cpp)