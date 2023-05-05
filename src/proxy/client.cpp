#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/stream.hpp>

#include "client.h"
#include "proxy_server.h"

using boost::asio::local::stream_protocol;

enum {
    max_length = 1024
};

gedsproxy::Client::Client() {
    this->io_context = new boost::asio::io_context();
    this->sock = new stream_protocol::socket(*io_context);
}

gedsproxy::Client::~Client() {
    delete this->sock;
    delete this->io_context;
}

void gedsproxy::Client::connect() {
    try {
        this->sock->connect(stream_protocol::endpoint(SOCKET_PATH));
        std::cout << "Connected to " << SOCKET_PATH << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
        throw e;
    }
}

ProxyResponse &gedsproxy::Client::call(ProxyRequest &request) {
//    boost::asio::io_context io_context;
//    stream_protocol::socket socket(io_context);
//    socket.connect(stream_protocol::endpoint(SOCKET_PATH));

//    using namespace std; // For strlen.
//    std::cout << "Enter message: ";
//    char requestBuff[max_length];
//    std::cin.getline(requestBuff, max_length);
//    size_t request_length = strlen(requestBuff);
//    boost::asio::write(*this->sock, boost::asio::buffer(requestBuff, request_length));
//
//    char reply[max_length];
//    size_t reply_length = boost::asio::read(*this->sock,
//                                            boost::asio::buffer(reply, request_length));
//    std::cout << "Reply is: ";
//    std::cout.write(reply, reply_length);
//    std::cout << "\n";

    char buf[1024*10];
    size_t buf_sz;
    {
        boost::iostreams::stream<boost::iostreams::array_sink> os(buf);
        boost::archive::binary_oarchive archive(os);
        archive << request;
        buf_sz = os.tellp();
    }
    std::cout << "Sending payload - size = " << buf_sz << std::endl;
    boost::asio::write(*this->sock,
                       boost::asio::buffer(buf, buf_sz));

    return *(new ProxyResponse());
}
