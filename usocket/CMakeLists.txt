cmake_minimum_required(VERSION 3.25)

project(UnixSocket 
    VERSION 0.1.0
    DESCRIPTION "a C++ wrapper around unix sockets"
    LANGUAGES CXX
)

set(SOURCES
    src/UnixDataSocket.cc
    src/UnixServerSocket.cc
    src/UnixClientConnect.cc
    src/Utils.cc
)

set(PUB_HEADERS
    include/nettools/UnixDataSocket.hh
    include/nettools/UnixServerSocket.hh
    include/nettools/UnixClientConnect.hh
)

set(PRIV_HEADERS
    src/Utils.hh
)

add_library(UnixSocketStatic STATIC)
target_sources(UnixSocketStatic 
    PRIVATE 
        ${SOURCES}
    PUBLIC
        FILE_SET pub_headers # public header file set associates the public with the target so that they can be used when building and installing
        TYPE HEADERS
        BASE_DIRS include # note that this is root of any #include directives
        FILES ${PUB_HEADERS} # here we list all the actual header files
    PRIVATE
        FILE_SET priv_headers
        TYPE HEADERS
        BASE_DIRS src
        FILES ${PRIV_HEADERS}
)

add_library(UnixSocketShared SHARED)
target_sources(UnixSocketShared 
    PRIVATE 
        ${SOURCES}
    PUBLIC
        FILE_SET pub_headers 
        TYPE HEADERS
        BASE_DIRS include
        FILES ${PUB_HEADERS}
    PRIVATE
        FILE_SET priv_headers
        TYPE HEADERS
        BASE_DIRS src
        FILES ${PRIV_HEADERS}
)

set(package_find_dir share/cmake/Nettools)

# defines what should be installed with the cmake --install command
install(TARGETS UnixSocketShared UnixSocketStatic
    EXPORT UnixSocketTargets # we also need to copy the file generated by install(EXPORT <name> ...) to the install tree
    FILE_SET pub_headers # also copies public headers from the file set to the install tree
)

# generates UnixSocketTargets.cmake for find_package in other cmake projects
install(EXPORT UnixSocketTargets
    NAMESPACE Nettools:: # adds namespaced to all installed targets
    DESTINATION ${package_find_dir}
)

# generates a version file for find_package VERSION
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/NettoolsConfigVersion.cmake
  COMPATIBILITY AnyNewerVersion
)

# installs the version and the config file for find_package into the install tree
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/NettoolsConfigVersion.cmake" # generated by write_basic_package_version_file
          "${CMAKE_CURRENT_SOURCE_DIR}/cmake/NettoolsConfig.cmake" # this file is predefined and simply includes the file generated by install(EXPORT ...)
    DESTINATION
        ${package_find_dir}
)


