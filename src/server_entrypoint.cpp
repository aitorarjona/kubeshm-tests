#include <boost/asio.hpp>
#include <iostream>

#include "proxy/server.h"

int main(int argc, char *argv[]) {
    std::remove(SOCKET_PATH.data());
    std::cout << "Starting server on " << SOCKET_PATH << std::endl;

    // create gedsproxy::Server instance
    gedsproxy::Server server;
    server.run();

    return 0;
}