cmake_minimum_required(VERSION 3.25)

project(test CXX)

find_package(Nettools CONFIG REQUIRED PATHS ../install/)

add_executable(server src/server.cc)

target_link_libraries(server PRIVATE Nettools::UnixSocketStatic)

add_executable(client src/client.cc)

target_link_libraries(client PRIVATE Nettools::UnixSocketStatic)

