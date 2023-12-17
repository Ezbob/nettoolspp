
#include "nettools/UnixClientConnect.hh"
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>
#include <algorithm>

std::shared_ptr<nettools::UnixDataSocket> nettools::connectToSocket(std::string const & path) {
    int fd = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (fd == -1) {
        return std::shared_ptr<nettools::UnixDataSocket>();
    }

    struct sockaddr_un addr = { 0 };
    addr.sun_family = AF_UNIX;
    std::copy_n(path.c_str(), sizeof(addr.sun_path) - 1, addr.sun_path);

    if (connect(fd, (struct sockaddr const*)(&addr), sizeof(addr)) == -1) {
        return std::shared_ptr<nettools::UnixDataSocket>();
    }
    return std::make_shared<nettools::UnixDataSocket>(fd);
}

