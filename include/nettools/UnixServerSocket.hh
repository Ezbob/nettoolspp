
#pragma once

#include <string>
#include "nettools/UnixDataSocket.hh"

namespace nettools {

    class UnixServerSocket {
    public:
        explicit UnixServerSocket(std::string const&, size_t backlog = 20);
        virtual ~UnixServerSocket();

        std::shared_ptr<UnixDataSocket> accept() noexcept;

        std::string const& path() const;
    private:
        std::string addr_;
        int fd_ = -1;
    };
}

