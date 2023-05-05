//
// Created by aitor on 5/05/23.
//

#include "ipc_queue_server.h"
#include "protocol.h"
#include "proxy_server.h"
#include <iostream>

void gedsproxy::BoostIPCQueueServer::setup() {
    try {
        boost::interprocess::message_queue::remove(PROXY_QUEUE_NAME.c_str());
        this->mq_ = new boost::interprocess::message_queue(
                boost::interprocess::create_only, PROXY_QUEUE_NAME.c_str(), 100, sizeof(ProxyRequest));
    } catch (boost::interprocess::interprocess_exception &ex) {
        std::cout << ex.what() << std::endl;
        throw ex;
    }
}

void gedsproxy::BoostIPCQueueServer::run() {
    ProxyRequest request;
    unsigned int priority;
    boost::interprocess::message_queue::size_type recvd_size;
    while (true) {
        try {
            mq_->receive(&request, sizeof(ProxyRequest), recvd_size, priority);

            std::cout << request.key << std::endl;
            std::cout << request.operation << std::endl;
            std::cout << request.range0 << std::endl;
            std::cout << request.range1 << std::endl;
            std::cout << request.replyQueue << std::endl;

            std::unique_ptr<ProxyResponse> response;
            switch (request.operation) {
                case OPEN:
                    response = this->server_.handle_open(request);
                    break;
                case CLOSE:
                    response = this->server_.handle_close(request);
                    break;
            }

            std::cout << response->message << std::endl;

            // check if response queue is stored
            if (replyQueues_.find(request.replyQueue) == replyQueues_.end()) {
                // if it is not, open response queue
                replyQueues_[request.replyQueue] =
                        std::make_unique<boost::interprocess::message_queue>(
                                boost::interprocess::open_only, request.replyQueue.c_str());
            }
            // get response queue from map
            replyQueues_.find(request.replyQueue)
                    ->second->send(response.get(), sizeof(ProxyResponse), 0);
        } catch (boost::interprocess::interprocess_exception &ex) {
            std::cout << ex.what() << std::endl;
            throw ex;
        }
    }
}

gedsproxy::BoostIPCQueueServer::BoostIPCQueueServer(gedsproxy::Server &proxyServer)
        : server_(proxyServer), mq_(nullptr) {}
