add_executable(server server1.cpp proxy/server.cpp proxy/server.h)
add_executable(client client2.cpp proxy/server.cpp proxy/server.h proxy/client.cpp proxy/client.h)
#target_link_libraries(geds
#        PRIVATE
#        absl::flags
#        absl::flags_parse
#        libgeds)