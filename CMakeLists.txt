cmake_minimum_required(VERSION 3.5.0)
project(gameinstaller)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsized-deallocation")

add_subdirectory(src)