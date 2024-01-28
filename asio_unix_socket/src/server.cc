#include <iostream>
#include <asio.hpp>
#include <string>

int main() 
{
    try
    {
        std::string data = "Hello there";
        asio::io_context io;

        asio::local::seq_packet_protocol::endpoint endpoint("/tmp/draw.sock");
        
        asio::local::seq_packet_protocol::acceptor acceptor(io, endpoint);

        acceptor.async_accept([&data](std::error_code ec, asio::local::seq_packet_protocol::socket socket) {
            if (ec) {
                std::cerr << "error stuff" << ec << std::endl;
                return;
            }
            std::cout << "Hello there!\n";
            asio::error_code ecc;
            std::size_t ss = socket.send(asio::buffer(data), 0, ecc);
            if (!ecc) {
                std::cout << "wrote --> " << ss << std::endl;
            } else {
                std::cerr << "error code " << ec << std::endl;
            }

            socket.close();
        }); 
        
        io.run();
    }
    catch (std::exception &e)
    {
        std::cout << "exception! " << e.what() << std::endl;
    }
    return 0;
}

