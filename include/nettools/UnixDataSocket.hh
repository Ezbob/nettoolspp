
#pragma once

#include <memory>
#include <string>

namespace nettools {

    class UnixDataSocket : public std::enable_shared_from_this<UnixDataSocket> {
        public:
            explicit UnixDataSocket(int fd);
            virtual ~UnixDataSocket();

            bool read(uint8_t *, size_t);
            bool write(const uint8_t *, size_t);

            std::shared_ptr<UnixDataSocket> get();
        private:
            int fd_ = -1;
            bool nonblocking_ = false;
    };
}

