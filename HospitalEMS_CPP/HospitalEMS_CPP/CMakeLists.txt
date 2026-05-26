cmake_minimum_required(VERSION 4.0)
project(HospitalEMS_CPP)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(HospitalEMS_CPP
        include/AVLTree.h
        include/BinomialHeap.h
        include/ConsoleUI.h
        include/DSU.h
        include/HospitalSystem.h
        include/Patient.h
        src/AVLTree.cpp
        src/BinomialHeap.cpp
        src/ConsoleUI.cpp
        src/DSU.cpp
        src/HospitalSystem.cpp
        src/main.cpp
        src/Patient.cpp)
