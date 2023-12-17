cmake_minimum_required(VERSION 3.25)

project(test CXX)

find_package(UnixSocket CONFIG REQUIRED PATHS /home/anders/Documents/usocket/install/)

add_executable(test src/main.cc)

target_link_libraries(test PRIVATE UnixSocket::UnixSocketStatic)
