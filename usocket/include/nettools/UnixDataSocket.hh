
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
            bool write(const char *, size_t);
            bool write(std::string const& content);

            std::shared_ptr<UnixDataSocket> get();

            bool nonblocking() const;
            void nonblocking(bool);

            int fd() const;
            
            bool closed() const;
            void close();
        private:
            int fd_ = -1;
            bool nonblocking_ = false;
    };
}

