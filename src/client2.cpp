#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>

const std::string socket_path = "/dev/shm/asio.localstream.socket";

using boost::asio::local::stream_protocol;

enum { max_length = 1024 };

int main(int argc, char* argv[])
{
    try
    {
        boost::asio::io_context io_context;

        stream_protocol::socket s(io_context);
        s.connect(stream_protocol::endpoint(socket_path));

        using namespace std; // For strlen.
        std::cout << "Enter message: ";
        char request[max_length];
        std::cin.getline(request, max_length);
        size_t request_length = strlen(request);
        boost::asio::write(s, boost::asio::buffer(request, request_length));

        char reply[max_length];
        size_t reply_length = boost::asio::read(s,
                                                boost::asio::buffer(reply, request_length));
        std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << "\n";
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}