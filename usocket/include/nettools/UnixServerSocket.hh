
#pragma once

#include <string>
#include <memory>
#include "nettools/UnixDataSocket.hh"

namespace nettools {

    class UnixServerSocket {
    public:
        explicit UnixServerSocket(std::string const&);
        virtual ~UnixServerSocket();

        bool listen(size_t backlog);

        std::shared_ptr<UnixDataSocket> accept() noexcept;

        std::string const& path() const;
    private:
        std::string addr_;
        int fd_ = -1;
    };

    std::unique_ptr<UnixServerSocket> serverListen(std::string const&, size_t backlog = 20);
}

