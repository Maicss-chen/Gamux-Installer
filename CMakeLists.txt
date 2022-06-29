#set(CMAKE_PREFIX_PATH /home/maicss/qt-5.11-static-simp-amd64)

# set(CMAKE_EXE_LINKER_FLAGS "-static")
# set(Qt6_FOUND TRUE)

cmake_minimum_required(VERSION 3.22)
project(gameinstaller)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsized-deallocation")

add_subdirectory(src)