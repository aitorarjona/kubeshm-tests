//
// Created by aitor on 2/05/23.
//

#ifndef KUBESHM_TESTS_PROXY_SERVER_H
#define KUBESHM_TESTS_PROXY_SERVER_H

#include <string>
#include <unordered_map>
#include <memory>

#include "protocol.h"


namespace gedsproxy {

    class Server {
    private:
        // hashmap of string, int
        std::unordered_map<std::string, int> open_shm_files_{};
    public:
        // define GEDSProxy constructor
        Server() = default;

        // define GEDSProxy destructor
        ~Server() = default;

        std::unique_ptr<ProxyResponse> handle_open(ProxyRequest &request);
        std::unique_ptr<ProxyResponse> handle_close(ProxyRequest &request);
    };

    void run_unix_sockets(Server &proxyServer);

    void run_ipc_queues(Server &proxyServer);
} // namespace gedsproxy

#endif // KUBESHM_TESTS_PROXY_SERVER_H
