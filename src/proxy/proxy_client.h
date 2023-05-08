//
// Created by aitor on 2/05/23.
//
#include <boost/asio.hpp>
#include "protocol.h"

#ifndef KUBESHM_TESTS_CLIENT_H
#define KUBESHM_TESTS_CLIENT_H


namespace gedsproxy {
    class Client {
    private:
        std::unique_ptr<ProxyIPCClient> ipcClient;
    public:
        // define GEDSProxy constructor
        explicit Client(std::unique_ptr<ProxyIPCClient> ipcClient);

        // define GEDSProxy destructor
        ~Client() = default;

        void open(const std::string& pathname, int flags);

    };
}

#endif //KUBESHM_TESTS_CLIENT_H
