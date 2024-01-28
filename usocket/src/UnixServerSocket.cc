
#include "nettools/UnixServerSocket.hh"
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdexcept>
#include <errno.h>
#include <algorithm>
#include "Utils.hh"

using namespace nettools;

UnixServerSocket::UnixServerSocket(std::string const& path) 
: addr_(path)
{
}

UnixServerSocket::~UnixServerSocket() 
{
    if (fd_ != -1) {
       ::close(fd_);
    } 
    ::unlink(addr_.c_str());
}

bool UnixServerSocket::listen(size_t backlog) 
{
    fd_ = ::socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (fd_ == -1) {
        return false;
    }

    struct sockaddr_un addr = make_address(addr_); 
    int rc = ::bind(fd_, (struct sockaddr const*)&addr, sizeof(struct sockaddr_un));
    if (rc == -1) {
        return false;
    }
    rc = ::listen(fd_, backlog);
    if (rc == -1) {
        return false;
    }
    return true;
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


std::unique_ptr<UnixServerSocket> nettools::serverListen(std::string const& path, size_t backlog) {
    auto ptr = std::make_unique<UnixServerSocket>(path);
    if (ptr->listen(backlog)) {
        return std::move(ptr);
    }   
    else
    {
        return {};
    }
}

