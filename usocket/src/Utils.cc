#include "Utils.hh"
#include <algorithm>
#include <sys/socket.h>

struct sockaddr_un nettools::make_address(std::string const&path) {

    struct sockaddr_un addr = { 0 };
    addr.sun_family = AF_UNIX;
    std::copy_n(path.c_str(), sizeof(addr.sun_path) - 1, addr.sun_path);

    return addr;
}


