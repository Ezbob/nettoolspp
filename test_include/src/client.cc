#include "nettools/UnixClientConnect.hh"
#include <string>
#include <array>
#include <iostream>
#include <stdlib.h>

int main() {
    auto client = nettools::connectToSocket("/tmp/testsock.sock"); 

    if (client) {
        std::array<uint8_t, 256> buf;
        if (client->read(buf.data(), buf.size())) {
            std::string msg(reinterpret_cast<char *>(buf.data()), buf.size());
            std::cout << "got " << msg << "\n";
        }
    } else {
        perror("client");
    }
}

