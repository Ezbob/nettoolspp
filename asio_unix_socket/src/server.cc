#include <iostream>
#include <asio.hpp>
#include <string>

using net_protocol = asio::local::seq_packet_protocol;


class Acceptor {
public:
    Acceptor(asio::io_context &io, net_protocol::endpoint const& endpoint) : m_io(io), m_acceptor(io, endpoint) {
    }

    void start() {
        m_acceptor.async_accept([this](asio::error_code ec, net_protocol::socket s) {
            accept(ec, std::move(s));
        });
    }

    void accept(asio::error_code ec, net_protocol::socket socket) {
        if (ec) {
            std::cerr << "error stuff" << ec << std::endl;
            return;
        }
        asio::error_code ecc;
        std::size_t ss = socket.send(asio::buffer("Hello there"), 0, ecc);
        if (!ecc) {
            std::cout << "wrote --> " << ss << std::endl;
        } else {
            std::cerr << "error code " << ec << std::endl;
        }
        m_acceptor.async_accept([this](asio::error_code ec, net_protocol::socket s) {
            accept(ec, std::move(s));
        });
    }

private:
    asio::io_context &m_io;
    net_protocol::acceptor m_acceptor;
};

    

int main() 
{
    try
    {
        asio::io_context io;

        net_protocol::endpoint endpoint("/tmp/draw.sock");
        
        Acceptor acc(io, endpoint);

        acc.start();

        io.run();
    }
    catch (std::exception &e)
    {
        std::cout << "exception! " << e.what() << std::endl;
    }
    return 0;
}

