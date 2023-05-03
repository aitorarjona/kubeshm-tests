//
// Created by aitor on 2/05/23.
//

#ifndef KUBESHM_TESTS_SERVER_H
#define KUBESHM_TESTS_SERVER_H

#include <string>

const std::string SOCKET_PATH = "/dev/shm/asio.localstream.socket";

namespace gedsproxy {
    class Server {
    public:
        // define GEDSProxy constructor
        Server() = default;

        // define GEDSProxy destructor
        ~Server() = default;

        // define GEDSProxy public methods
        // Start method
        void run();
    };
}


#endif //KUBESHM_TESTS_SERVER_H
