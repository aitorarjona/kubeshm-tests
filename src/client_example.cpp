#include "proxy/proxy_client.h"
#include "proxy/ipc/boost_mq.h"

int main(int argc, char *argv[]) {
    // create transport client
    gedsproxy::ProxyIPCClient *clientPtr = new gedsproxy::BoostIPCQueueClient();
    // make shared ptr
    std::unique_ptr<gedsproxy::ProxyIPCClient> client(clientPtr);

    // create proxy client
    gedsproxy::Client proxyClient(std::move(client));
    proxyClient.open("/tmp/example_file", O_RDWR | O_CREAT);

    return 0;
}
