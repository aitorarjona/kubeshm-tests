
find_package(Boost 1.78.0 COMPONENTS system filesystem serialization REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -pthread -lboost_serialization")

add_executable(server server_entrypoint.cpp proxy/proxy_server.cpp proxy/proxy_server.h proxy/protocol.cpp proxy/protocol.h proxy/unixsock_server.cpp proxy/unixsock_server.h proxy/ipc_queue_server.cpp proxy/ipc_queue_server.h)
add_executable(client client_example.cpp proxy/proxy_server.cpp proxy/proxy_server.h proxy/client.cpp proxy/client.h proxy/protocol.cpp proxy/protocol.h proxy/unixsock_server.cpp proxy/unixsock_server.h proxy/ipc_queue_server.cpp proxy/ipc_queue_server.h)
#target_link_libraries(geds
#        PRIVATE
#        absl::flags
#        absl::flags_parse
#        libgeds)