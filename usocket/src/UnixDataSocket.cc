
#include "nettools/UnixDataSocket.hh"
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdexcept>
#include <string.h>
#include <errno.h>

namespace {
    bool is_nonblocking_error() {
        return errno == EWOULDBLOCK || errno == EAGAIN;
    }
}

using namespace nettools;

UnixDataSocket::UnixDataSocket(int fd) : fd_(fd) {}

UnixDataSocket::~UnixDataSocket() {
}

bool UnixDataSocket::read(uint8_t *data, size_t length) {
    int rc = ::read(fd_, data, length);
    if (rc == -1) {
        return nonblocking_ && is_nonblocking_error();
    }
    return true;
}

bool UnixDataSocket::write(std::string const& content) {
    return write(content.c_str(), content.size());
}

bool UnixDataSocket::write(const uint8_t *data, size_t length) {
    int rc = ::write(fd_, data, length);
    if (rc == -1) {
        return nonblocking_ && is_nonblocking_error();
    }
    return true;
}

bool UnixDataSocket::write(const char *data, size_t length) {
    int rc = ::write(fd_, data, length);
    if (rc == -1) {
        return nonblocking_ && is_nonblocking_error();
    }
    return true;
}

std::shared_ptr<UnixDataSocket> UnixDataSocket::get() {
    return shared_from_this();
}

void UnixDataSocket::nonblocking(bool should_not_block) {
    int flags = fcntl(fd_, F_GETFL);
    if (flags == -1) {
        throw std::runtime_error(strerror(errno));
    } 
    flags = should_not_block ? (flags | O_NONBLOCK) : (flags & ~(O_NONBLOCK));

    if (fcntl(fd_, F_SETFL, flags) == -1) {
        throw std::runtime_error(strerror(errno));
    }
}

bool UnixDataSocket::nonblocking() const {
    return nonblocking_;
}

int UnixDataSocket::fd() const {
    return fd_;
}

void UnixDataSocket::close() {
    if (fd_ != -1) {
        ::close(fd_);
        fd_ = -1;
    }
}

bool UnixDataSocket::closed() const {
    return fd_ == -1;
}
