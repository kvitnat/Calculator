cmake_minimum_required(VERSION 3.15)
project(calculator)

set(CMAKE_CXX_STANDARD 14)

add_executable(calculator main.cpp cmake-build-debug/myParser.cpp cmake-build-debug/myParser.h)