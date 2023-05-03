//
// Created by aitor on 2/05/23.
//
#include <boost/asio.hpp>
#include "protocol.h"

#ifndef KUBESHM_TESTS_CLIENT_H
#define KUBESHM_TESTS_CLIENT_H

using boost::asio::local::stream_protocol;

namespace gedsproxy {
    class Client {
    private:
        boost::asio::basic_stream_socket<stream_protocol> *sock;
        boost::asio::io_context *io_context;
    public:
        // define GEDSProxy constructor
        Client();

        // define GEDSProxy destructor
        ~Client();

        void connect();

        ProxyResponse& call(ProxyRequest& request);
    };
}

#endif //KUBESHM_TESTS_CLIENT_H
