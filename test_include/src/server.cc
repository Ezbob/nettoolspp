#include "nettools/UnixServerSocket.hh"
#include <signal.h>
#include <unistd.h>
#include <atomic>

std::atomic<bool> want_to_quit(false);

void got_signal(int) {
    want_to_quit.store(true);
}

int main() { 

    struct sigaction sa = { 0 };
    sa.sa_handler = got_signal;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT, &sa, nullptr);
    sigaction(SIGTERM, &sa, nullptr);

    auto socket = nettools::UnixServerSocket("/tmp/testsock.sock");

    for (;;) {
        auto data_socket = socket.accept();
        if (data_socket) {
            data_socket->write("Hello there!");
        }
        if (want_to_quit.load()) {
            break;
        }
    }
}

