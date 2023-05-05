#include "proxy/proxy_server.h"

int main(int argc, char *argv[]) {
    gedsproxy::Server server;
    gedsproxy::run_ipc_queues(server);
    return 0;
}