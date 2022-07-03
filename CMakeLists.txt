cmake_minimum_required(VERSION 3.5.0)
project(gamux-installer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsized-deallocation")
add_definitions(-DVERSION="1.0.0")
add_subdirectory(src)
add_subdirectory(tools)