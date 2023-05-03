#include "proxy/client.h"

int main(int argc, char *argv[]) {

    // create gedsproxy::Client instance
    gedsproxy::Client client;
    client.connect();

    ProxyRequest request;
    request.operation = ProxyCommand::OPEN;
    request.key = "test";
    request.range0 = 0;
    request.range1 = 10;
    client.call(request);

    return 0;
}
