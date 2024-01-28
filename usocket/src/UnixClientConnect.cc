
#include "nettools/UnixClientConnect.hh"
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <errno.h>
#include <algorithm>
#include "Utils.hh"

std::shared_ptr<nettools::UnixDataSocket> nettools::connectToSocket(std::string const & path) {
    int fd = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (fd == -1) {
        return std::shared_ptr<nettools::UnixDataSocket>();
    }
    struct sockaddr_un addr = make_address(path);
    if (connect(fd, (struct sockaddr const*)(&addr), sizeof(addr)) == -1) {
        return std::shared_ptr<nettools::UnixDataSocket>();
    }
    return std::make_shared<nettools::UnixDataSocket>(fd);
}

