cmake_minimum_required(VERSION 3.14)
project(BTree CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

# Main executable (interactive shell + demo)
add_executable(btree src/main.cpp)

# Test executable
add_executable(btree_tests tests/test_btree.cpp)

# CTest integration
enable_testing()
add_test(NAME BTreeTests COMMAND btree_tests)