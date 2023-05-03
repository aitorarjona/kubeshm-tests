
find_package(Boost 1.78.0 COMPONENTS system filesystem serialization REQUIRED)

set(CMAKE_CXX_FLAGS "-std=c++20 -Wall -pthread -lboost_serialization")

add_executable(server server_entrypoint.cpp proxy/server.cpp proxy/server.h)
add_executable(client client_example.cpp proxy/server.cpp proxy/server.h proxy/client.cpp proxy/client.h proxy/protocol.cpp proxy/protocol.h)
#target_link_libraries(geds
#        PRIVATE
#        absl::flags
#        absl::flags_parse
#        libgeds)