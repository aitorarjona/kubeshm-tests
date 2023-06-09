#include <iostream>

#include <boost/asio.hpp>

#include "proxy_server.h"
#include "ipc/boost_unixsock.h"
#include "ipc/boost_mq.h"

void gedsproxy::run_unix_sockets(gedsproxy::Server &proxyServer) {
    std::cout << "Proxy Server run_unix_sock" << std::endl;
    boost::asio::io_context io_context;
    gedsproxy::BoostAFUnixServer s(proxyServer, io_context);
    io_context.run();
}

void gedsproxy::run_ipc_queues(gedsproxy::Server &proxyServer) {
    std::cout << "Proxy Server run_ipc_queues" << std::endl;
    gedsproxy::BoostIPCQueueServer s(proxyServer);
    s.setup();
    s.run();
}

std::unique_ptr<gedsproxy::ProxyResponse> gedsproxy::Server::handle_open(ProxyRequest &request) {
    std::cout << "Proxy Server handle_open" << std::endl;
    ProxyResponse response {
        .message = "ok\0"
    };
    return std::make_unique<ProxyResponse>(response);

    // check if the file is already open
//    ProxyResponse response{};
//    if (this->open_shm_files_.find(request.key) != this->open_shm_files_.end()) {
//        // if it is, put "ok" in response message
//        strcpy(response.message, "ok\0");
//    } else {
//        // if it is not, create the shared memory object
//        int fd = shm_open(request.key, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
//        if (fd == -1) {
//            perror("cagaste 1");
//            exit(-1);
//        }
//
//        // set the size of the shared memory object
//        size_t sz = request.range1 - request.range0;
//        assert(sz > 0);
//        int ft = ftruncate(fd, sz);
//        if (ft == -1) {
//            perror("cagaste 2");
//            exit(-1);
//        }
//
//        // map the shared memory object to process memory
//        void *addr = mmap(nullptr, sz, PROT_WRITE, MAP_SHARED, fd, 0);
//        if (addr == MAP_FAILED) {
//            perror("cagaste 3");
//            exit(-1);
//        }
//
//        // write some data to the shared memory object
//        memset(addr, '#', sz);
//
//        this->open_shm_files_.insert({request.key, fd});
//        response.message = "ok";
//    }

    return std::make_unique<ProxyResponse>(response);
}

std::unique_ptr<gedsproxy::ProxyResponse> gedsproxy::Server::handle_close(ProxyRequest &request) {
    return nullptr;
}
