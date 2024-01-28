
#include <iostream>
#include <asio.hpp>
#include <array>

int main() {

    asio::io_context io;

    asio::local::seq_packet_protocol::socket socket(io);
    asio::local::seq_packet_protocol::endpoint endpoint("/tmp/draw.sock");

    socket.connect(endpoint);

    decltype(socket)::message_flags fs;
    asio::error_code ec;
    std::array<char, 256> a;
    a.fill('\0');
    socket.receive(asio::buffer(a, a.size()),0, fs, ec);
    if (ec) {
        std::cout << "bad\n";
        return 1;
    }
    
    for (char c : a) {
        if (c == '\0') break;
        std::cout << c;
    }

    return 0;
}

