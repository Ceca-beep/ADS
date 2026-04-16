cmake_minimum_required(VERSION 3.14)
project(BinomialHeap CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

add_executable(bheap src/main.cpp)
add_executable(bheap_tests tests/test_binomial_heap.cpp)

enable_testing()
add_test(NAME BinomialHeapTests COMMAND bheap_tests)