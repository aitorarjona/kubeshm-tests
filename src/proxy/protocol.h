//
// Created by aitor on 3/05/23.
//

#ifndef KUBESHM_TESTS_PROTOCOL_H
#define KUBESHM_TESTS_PROTOCOL_H

#include <string>
#include <tuple>

enum ProxyCommand {
    OPEN,
    CLOSE
};

struct ProxyRequest {
    ProxyCommand operation;
    std::string key;
    unsigned long range0;
    unsigned long range1;
    std::string replyQueue;

    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & operation;
        ar & key;
        ar & range0;
        ar & range1;
    }
};

struct ProxyResponse {
    std::string message;

    template<typename Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & message;
    }
};

#endif //KUBESHM_TESTS_PROTOCOL_H
