cmake_minimum_required(VERSION 3.25)

project(test CXX)

find_package(UnixSocket CONFIG REQUIRED PATHS /home/anders/Documents/usocket/install/)

add_executable(server src/server.cc)

target_link_libraries(server PRIVATE UnixSocket::UnixSocketStatic)

add_executable(client src/client.cc)

target_link_libraries(client PRIVATE UnixSocket::UnixSocketStatic)

