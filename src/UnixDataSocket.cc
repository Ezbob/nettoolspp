
#include "nettools/UnixDataSocket.hh"
#include <unistd.h>
#include <errno.h>

namespace {
    bool is_nonblocking_error() {
        return errno == EWOULDBLOCK || errno == EAGAIN;
    }
}

using namespace nettools;

UnixDataSocket::UnixDataSocket(int fd) : fd_(fd) {}

UnixDataSocket::~UnixDataSocket() {
    if (fd_ != -1) close(fd_);
}

bool UnixDataSocket::read(uint8_t *data, size_t length) {
    int rc = ::read(fd_, data, length);
    if (rc == -1) {
        return nonblocking_ && is_nonblocking_error();
    }
    return true;
}

bool UnixDataSocket::write(const uint8_t *data, size_t length) {
    int rc = ::write(fd_, data, length);
    if (rc == -1) {
        return nonblocking_ && is_nonblocking_error();
    }
    return true;
}

std::shared_ptr<UnixDataSocket> UnixDataSocket::get() {
    return shared_from_this();
}

