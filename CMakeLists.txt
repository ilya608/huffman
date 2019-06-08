cmake_minimum_required(VERSION 3.10)
project(huffman)

if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14 -pedantic")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif ()
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++11 -pthread")

include_directories(console)
include_directories(lib/headers)
include_directories(tester/gtest)

set(CONSOLE_FILES
        console/file_compressor.h
        console/file_compressor.cpp
        console/file_decompressor.h
        console/file_decompressor.cpp
        console/file_writer.h
        console/file_reader.h
        console/file_writer.cpp
        console/file_reader.cpp)
set(LIB
        lib/headers/consts.h
        lib/headers/counter.h
        lib/headers/decoder.h
        lib/headers/encoded_bytes.h
        lib/headers/encoder.h
        lib/headers/huffman_tree.h
        lib/counter.cpp
        lib/decoder.cpp
        lib/encoded_bytes.cpp
        lib/encoder.cpp
        lib/huffman_tree.cpp)

add_executable(Console
        ${CONSOLE_FILES}
        ${LIB}
        console/main.cpp)

add_executable(Huffman_test
        ${CONSOLE_FILES}
        ${LIB}
        tester/gtest/gtest-all.cc
        tester/gtest/gtest.h
        tester/gtest/gtest_main.cc
        tester/tree_testing
        )

target_link_libraries(Console -lpthread)
target_link_libraries(Huffman_test -lpthread)
