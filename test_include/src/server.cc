#include "nettools/UnixServerSocket.hh"

int main() { 
    nettools::UnixServerSocket socket("/tmp/testsock.sock");

    for (;;) {
        auto data_socket = socket.accept();
        if (data_socket) {
            data_socket->write("Hello there!");
        }
    }
}

