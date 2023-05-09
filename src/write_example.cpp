#include "proxy/proxy_client.h"
#include "proxy/ipc/boost_mq.h"

int main(int argc, char *argv[]) {
    std::unique_ptr<gedsproxy::ProxyIPCClient> clientImpl = std::make_unique<gedsproxy::BoostIPCQueueClient>();

    gedsproxy::Client proxyClient(std::move(clientImpl));
    proxyClient.open("/tmp/example_file", O_RDWR | O_CREAT);

    return 0;
}
