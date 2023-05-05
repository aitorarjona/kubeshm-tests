//
// Created by aitor on 5/05/23.
//

#include <boost/archive/binary_iarchive.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>

#include "protocol.h"
#include "proxy_server.h"

#ifndef KUBESHM_TESTS_UNIXSOCK_SERVER_H
#define KUBESHM_TESTS_UNIXSOCK_SERVER_H

const std::string SOCKET_PATH = "/dev/shm/asio.localstream.socket";


namespace gedsproxy {
    class BoostAFUnixSession : public std::enable_shared_from_this<BoostAFUnixSession> {
    private:
        gedsproxy::Server &server_;
        boost::asio::local::stream_protocol::socket socket_;
        char data_[1024 * 10];

    public:
        BoostAFUnixSession(gedsproxy::Server &server, boost::asio::io_context &io_context);

        boost::asio::local::stream_protocol::socket &socket();

        void start();

        void handle_read(const boost::system::error_code &error, size_t bytes_transferred);

        void handle_write(const boost::system::error_code &error);
    };

    class BoostAFUnixServer {
    private:
        gedsproxy::Server &server_;
        boost::asio::io_context &io_context_;
        boost::asio::local::stream_protocol::acceptor acceptor_;

    public:
        BoostAFUnixServer(gedsproxy::Server &server, boost::asio::io_context &io_context);

        void handle_accept(std::shared_ptr<BoostAFUnixSession> session,
                           const boost::system::error_code &error);
    };
}


#endif //KUBESHM_TESTS_UNIXSOCK_SERVER_H
