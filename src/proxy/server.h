//
// Created by aitor on 2/05/23.
//

#ifndef KUBESHM_TESTS_SERVER_H
#define KUBESHM_TESTS_SERVER_H

namespace gedsproxy {
    class Server {
    public:
        // define GEDSProxy constructor
        Server() = delete;

        // define GEDSProxy destructor
        ~Server() = delete;

        // define GEDSProxy public methods
        // Start method
        void start();
    };
}


#endif //KUBESHM_TESTS_SERVER_H
