//
// Created by aitor on 3/05/23.
//

#ifndef KUBESHM_TESTS_PROTOCOL_H
#define KUBESHM_TESTS_PROTOCOL_H

#include <string>
#include <tuple>

namespace gedsproxy {
    enum ProxyOperation {
        OPEN,
        CLOSE
    };

    struct ProxyRequest {
        ProxyOperation operation;
        char key[256];
        unsigned long range0;
        unsigned long range1;
        char replyQueue[256];

        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & operation;
            ar & key;
            ar & range0;
            ar & range1;
        }
    };

    struct ProxyResponse {
        char message[256];

        template<typename Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & message;
        }
    };

    class ProxyIPCClient {
    public:
        virtual ~ProxyIPCClient() = default;
        virtual std::unique_ptr<ProxyResponse> call(ProxyRequest& request) = 0;
    };
}

#endif //KUBESHM_TESTS_PROTOCOL_H
