#include <boost/archive/binary_iarchive.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>

#include "protocol.h"
#include "proxy_server.h"
#include "unixsock_server.h"

gedsproxy::BoostAFUnixSession::BoostAFUnixSession(gedsproxy::Server &server, boost::asio::io_context &io_context)
    : server_(server), socket_(io_context) {}

boost::asio::local::stream_protocol::socket &gedsproxy::BoostAFUnixSession::socket() {
    return socket_;
}

void gedsproxy::BoostAFUnixSession::start() {
    std::cout << "BoostAFUnixSession start" << std::endl;
    socket_.async_read_some(boost::asio::buffer(data_),
                            boost::bind(&BoostAFUnixSession::handle_read, shared_from_this(),
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
}

void gedsproxy::BoostAFUnixSession::handle_read(const boost::system::error_code &error,
                                                size_t bytes_transferred) {
    std::cout << "--- BoostAFUnixSession handle_read ---" << std::endl;
    if (!error) {
        ProxyRequest request;
        {
            boost::iostreams::stream<boost::iostreams::array_source> is(data_);
            boost::archive::binary_iarchive ia(is);
            ia >> request;
        }

        std::cout << request.key << std::endl;
        std::cout << request.operation << std::endl;
        std::cout << request.range0 << std::endl;
        std::cout << request.range1 << std::endl;

        boost::asio::async_write(socket_, boost::asio::buffer(data_, bytes_transferred),
                                 boost::bind(&BoostAFUnixSession::handle_write, shared_from_this(),
                                             boost::asio::placeholders::error));
    } else {
        // print what error occured
        std::cout << error.message() << std::endl;
    }
    std::cout << "--- BoostAFUnixSession handle_read ---" << std::endl;
}

void gedsproxy::BoostAFUnixSession::handle_write(const boost::system::error_code &error) {
    std::cout << "--- BoostAFUnixSession handle_write ---" << std::endl;
    if (!error) {
        socket_.async_read_some(boost::asio::buffer(data_),
                                boost::bind(&BoostAFUnixSession::handle_read, shared_from_this(),
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
    } else {
        // print what error occured
        std::cout << error.message() << std::endl;
    }
    std::cout << "--- BoostAFUnixSession handle_write ---" << std::endl;
}

/////////////////////////////////////

gedsproxy::BoostAFUnixServer::BoostAFUnixServer(gedsproxy::Server &server, boost::asio::io_context &io_context)
    : server_(server), io_context_(io_context),
      acceptor_(io_context, boost::asio::local::stream_protocol::endpoint(SOCKET_PATH)) {
    std::shared_ptr<BoostAFUnixSession> new_session(new BoostAFUnixSession(server, io_context_));
    std::cout << "BoostAFUnixServer" << std::endl;
    acceptor_.async_accept(new_session->socket(),
                           boost::bind(&BoostAFUnixServer::handle_accept, this, new_session,
                                       boost::asio::placeholders::error));
}

void gedsproxy::BoostAFUnixServer::handle_accept(std::shared_ptr<BoostAFUnixSession> session,
                                                 const boost::system::error_code &error) {
    std::cout << "handle_accept" << std::endl;
    if (!error) {
        session->start();
    }
    session.reset(new BoostAFUnixSession(this->server_, io_context_));
    acceptor_.async_accept(session->socket(),
                           boost::bind(&BoostAFUnixServer::handle_accept, this, session,
                                       boost::asio::placeholders::error));
}

// class BoostAFUnixSession : public std::enable_shared_from_this<BoostAFUnixSession> {
// private:
//     // The socket used to communicate with the client.
//     boost::asio::local::stream_protocol::socket socket_;
//     // Buffer used to store data received from the client.
//     char data_[1024 * 10];
//
// public:
//     BoostAFUnixSession(boost::asio::io_context &io_context) : socket_(io_context) {}
//
//     boost::asio::local::stream_protocol::socket &socket() { return socket_; }
//
//     void start() {
//         std::cout << "BoostAFUnixSession start" << std::endl;
//         socket_.async_read_some(boost::asio::buffer(data_),
//                                 boost::bind(&BoostAFUnixSession::handle_read,
//                                 shared_from_this(),
//                                             boost::asio::placeholders::error,
//                                             boost::asio::placeholders::bytes_transferred));
//     }
//
//     void handle_read(const boost::system::error_code &error, size_t bytes_transferred) {
//         std::cout << "--- BoostAFUnixSession handle_read ---" << std::endl;
//         if (!error) {
//             ProxyRequest request;
//             {
//                 boost::iostreams::stream<boost::iostreams::array_source> is(data_);
//                 boost::archive::binary_iarchive ia(is);
//                 ia >> request;
//             }
//
//             std::cout << request.key << std::endl;
//             std::cout << request.operation << std::endl;
//             std::cout << request.range0 << std::endl;
//             std::cout << request.range1 << std::endl;
//
//             boost::asio::async_write(socket_, boost::asio::buffer(data_, bytes_transferred),
//                                      boost::bind(&BoostAFUnixSession::handle_write,
//                                                  shared_from_this(),
//                                                  boost::asio::placeholders::error));
//         } else {
//             // print what error occured
//             std::cout << error.message() << std::endl;
//         }
//         std::cout << "--- BoostAFUnixSession handle_read ---" << std::endl;
//     }
//
//     void handle_write(const boost::system::error_code &error) {
//         std::cout << "--- BoostAFUnixSession handle_write ---" << std::endl;
//         if (!error) {
//             socket_.async_read_some(boost::asio::buffer(data_),
//                                     boost::bind(&BoostAFUnixSession::handle_read,
//                                                 shared_from_this(),
//                                                 boost::asio::placeholders::error,
//                                                 boost::asio::placeholders::bytes_transferred));
//         }
//         std::cout << "--- BoostAFUnixSession handle_write ---" << std::endl;
//     }
// };
//
// class BoostAFUnixServer {
// private:
//     boost::asio::io_context &io_context_;
//     boost::asio::local::stream_protocol::acceptor acceptor_;
//
// public:
//     BoostAFUnixServer(boost::asio::io_context &io_context, const std::string &file)
//             : io_context_(io_context),
//               acceptor_(io_context, boost::asio::local::stream_protocol::endpoint(file)) {
//         std::shared_ptr<BoostAFUnixSession> new_session(new BoostAFUnixSession(io_context_));
//         std::cout << "BoostAFUnixServer" << std::endl;
//         acceptor_.async_accept(new_session->socket(),
//                                boost::bind(&BoostAFUnixServer::handle_accept, this, new_session,
//                                            boost::asio::placeholders::error));
//     }
//
//     void handle_accept(std::shared_ptr<BoostAFUnixSession> new_session,
//                        const boost::system::error_code &error) {
//         std::cout << "handle_accept" << std::endl;
//         if (!error) {
//             new_session->start();
//         }
//         new_session.reset(new BoostAFUnixSession(io_context_));
//         acceptor_.async_accept(new_session->socket(),
//                                boost::bind(&BoostAFUnixServer::handle_accept, this, new_session,
//                                            boost::asio::placeholders::error));
//     }
// };