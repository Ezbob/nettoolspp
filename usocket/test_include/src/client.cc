#include "nettools/UnixClientConnect.hh"
#include <string>
#include <array>
#include <iostream>
#include <stdlib.h>
#include <sys/ioctl.h>

int main() {
    auto client = nettools::connectToSocket("/tmp/testsock.sock"); 

    if (client) {
        size_t bytes_available = 0;
        if (ioctl(client->fd(), FIONREAD, &bytes_available) != -1) {
            std::cout << "bytes seen " << bytes_available << "\n";
        } else {
            std::cout << "not seen\n";
        }
        
        std::array<uint8_t, 256> buf;
        buf.fill(0);
        if (client->read(buf.data(), buf.size())) {
            std::string msg(reinterpret_cast<char *>(buf.data()));
            std::cout << "got " << msg << " " << msg.length() << "\n";
        }
    } else {
        perror("client");
    }
}

