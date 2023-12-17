
#include "nettools/UnixServerSocket.hh"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdexcept>
#include <errno.h>
#include <algorithm>

using namespace nettools;

UnixServerSocket::UnixServerSocket(std::string const& path, size_t backlog) : addr_(path)
{
    fd_ = ::socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (fd_ == -1) {
        throw std::runtime_error(strerror(errno));
    }

    struct sockaddr_un addr = { 0 };
    addr.sun_family = AF_UNIX;
    std::copy_n(path.c_str(), sizeof(addr.sun_path) - 1, addr.sun_path);

    int rc = ::bind(fd_, (struct sockaddr const*)&addr, sizeof(struct sockaddr_un));
    if (rc == -1) {
        throw std::runtime_error(strerror(errno));
    }
    
    rc = ::listen(fd_, backlog);
    if (rc == -1) {
        throw std::runtime_error(strerror(errno));
    }
}

UnixServerSocket::~UnixServerSocket() 
{
    if (fd_ != -1) {
       ::close(fd_);
    } 
    ::unlink(addr_.c_str());
}

std::string const& UnixServerSocket::path() const
{
    return addr_;
}

std::shared_ptr<UnixDataSocket> UnixServerSocket::accept() noexcept 
{
    int fd = ::accept(fd_, nullptr, nullptr);
    if (fd == -1) {
        return std::shared_ptr<UnixDataSocket>();
    }
    return std::make_shared<UnixDataSocket>(fd);
}

