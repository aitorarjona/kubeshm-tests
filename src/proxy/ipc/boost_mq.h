//
// Created by aitor on 5/05/23.
//

#include "boost/interprocess/ipc/message_queue.hpp"
#include "../proxy_server.h"
#include "../proxy_client.h"

#ifndef KUBESHM_TESTS_IPC_QUEUE_SERVER_H
#define KUBESHM_TESTS_IPC_QUEUE_SERVER_H

const std::string PROXY_QUEUE_NAME = "gedsproxy";


namespace gedsproxy {
    class BoostIPCQueueServer {
    private:
        gedsproxy::Server &server_;
        boost::interprocess::message_queue *mq_;
        std::unordered_map<std::string, std::unique_ptr<boost::interprocess::message_queue>> replyQueues_{};
    public:
        BoostIPCQueueServer(gedsproxy::Server &proxyServer);
        void setup();
        void run();
    };

    class BoostIPCQueueClient : public gedsproxy::ProxyIPCClient {
    private:
        boost::interprocess::message_queue *proxy_mq;
        boost::interprocess::message_queue *client_mq;
    public:
        BoostIPCQueueClient();

        std::unique_ptr<ProxyResponse> call(ProxyRequest &request) override;
    };
}

#endif //KUBESHM_TESTS_IPC_QUEUE_SERVER_H
