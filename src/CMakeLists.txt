
find_package(Boost 1.78.0 COMPONENTS system filesystem serialization REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -pthread -lboost_serialization")

add_executable(server server_entrypoint.cpp proxy/proxy_server.cpp proxy/proxy_server.h proxy/protocol.h proxy/ipc/boost_unixsock.cpp proxy/ipc/boost_unixsock.h proxy/ipc/boost_mq.cpp proxy/ipc/boost_mq.h)
add_executable(client client_example.cpp proxy/proxy_server.cpp proxy/proxy_server.h proxy/proxy_client.cpp proxy/proxy_client.h proxy/protocol.h proxy/ipc/boost_unixsock.cpp proxy/ipc/boost_unixsock.h proxy/ipc/boost_mq.cpp proxy/ipc/boost_mq.h)
#target_link_libraries(geds
#        PRIVATE
#        absl::flags
#        absl::flags_parse
#        libgeds)