//
// Created by aitor on 5/05/23.
//

#include "boost_mq.h"
#include <iostream>

gedsproxy::BoostIPCQueueServer::BoostIPCQueueServer(gedsproxy::Server &proxyServer)
    : server_(proxyServer), mq_(nullptr) {}

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
    // create ProxyRequest shared pointer
    ProxyRequest request;

    unsigned int priority;
    boost::interprocess::message_queue::size_type recvd_size;
    while (true) {
        try {
            std::cout << "Waiting for a message..." << std::endl;
            mq_->receive(&request, sizeof(ProxyRequest), recvd_size, priority);
            std::cout << "Received message of size " << recvd_size << std::endl;

            std::cout << request.key << std::endl;
//            std::cout << request.operation << std::endl;
//            std::cout << request.range0 << std::endl;
//            std::cout << request.range1 << std::endl;
            std::cout << request.replyQueue << std::endl;

            std::unique_ptr<ProxyResponse> response;
            switch (request.operation) {
            case OPEN:
                response = this->server_.handle_open(request);
                break;
            case CLOSE:
//                response = this->server_.handle_close(request);
                break;
            }

//            std::cout << response->message << std::endl;

            // check if response queue is stored
            if (replyQueues_.find(request.replyQueue) == replyQueues_.end()) {
                // if it is not, open response queue
                replyQueues_[request.replyQueue] =
                    std::make_unique<boost::interprocess::message_queue>(
                        boost::interprocess::open_only, request.replyQueue);
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

//////////////////////////////////////////

gedsproxy::BoostIPCQueueClient::BoostIPCQueueClient()
    : proxy_mq(nullptr), client_mq(nullptr) {
    try {
        this->proxy_mq = new boost::interprocess::message_queue(
            boost::interprocess::open_only, PROXY_QUEUE_NAME.c_str());
//        boost::interprocess::message_queue::remove("client_queue");
        this->client_mq = new boost::interprocess::message_queue(
            boost::interprocess::open_or_create, "client_queue", 100, sizeof(ProxyResponse));
    } catch (boost::interprocess::interprocess_exception &ex) {
        std::cout << ex.what() << std::endl;
        throw ex;
    }
}

std::unique_ptr<gedsproxy::ProxyResponse> gedsproxy::BoostIPCQueueClient::call(ProxyRequest &request) {
    try {
        std::cout << "Sending message" << std::endl;
        this->proxy_mq->send(&request, sizeof(ProxyRequest), 0);
        unsigned int priority;
        boost::interprocess::message_queue::size_type recvd_size;
        ProxyResponse response;
        std::cout << "Waiting for a response..." << std::endl;
        this->client_mq->receive(&response, sizeof(ProxyResponse), recvd_size, priority);
        std::cout << "Response received" << std::endl;
        return std::make_unique<ProxyResponse>(response);
    } catch (boost::interprocess::interprocess_exception &ex) {
        std::cout << ex.what() << std::endl;
        throw ex;
    }
}
