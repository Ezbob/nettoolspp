cmake_minimum_required(VERSION 3.25)

project(asionet CXX)

include(FetchContent)

FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-29-0
)

FetchContent_MakeAvailable(
    asio
)

add_library(asiolib INTERFACE)
target_include_directories(asiolib INTERFACE ${asio_SOURCE_DIR}/asio/include)

add_executable(server)
target_sources(server PRIVATE src/server.cc)
target_link_libraries(server PRIVATE asiolib)

add_executable(client)
target_sources(client PRIVATE src/client.cc)
target_link_libraries(client PRIVATE asiolib)
