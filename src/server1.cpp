#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>

const std::string socket_path = "/dev/shm/asio.localstream.socket";

using boost::asio::local::stream_protocol;

class session : public std::enable_shared_from_this<session> {
private:
    // The socket used to communicate with the client.
    stream_protocol::socket socket_;

    // Buffer used to store data received from the client.
    boost::array<char, 1024> data_;

public:
    session(boost::asio::io_context &io_context) : socket_(io_context) {}

    stream_protocol::socket &socket() { return socket_; }

    void start() {
        std::cout << "session start" << std::endl;
        socket_.async_read_some(
                boost::asio::buffer(data_),
                boost::bind(&session::handle_read, shared_from_this(),
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
    }

    void handle_read(const boost::system::error_code &error,
                     size_t bytes_transferred) {
        std::cout << "=== read done ===" << std::endl;
        if (!error) {
            std::cout << "mierdon" << std::endl;
            std::cout << data_.data() << std::endl;
            std::cout << bytes_transferred << std::endl;
            std::string message(data_.data(), bytes_transferred);
            std::transform(message.begin(), message.end(), message.begin(),
                           ::toupper);
            std::cout << message << std::endl;
            // write message to data_
            std::copy(message.begin(), message.end(), data_.begin());
            boost::asio::async_write(
                    socket_, boost::asio::buffer(data_, bytes_transferred),
                    boost::bind(&session::handle_write, shared_from_this(),
                                boost::asio::placeholders::error));
        } else {
            // print what error occured
            std::cout << error.message() << std::endl;
        }
    }

    void handle_write(const boost::system::error_code &error) {
        std::cout << "=== write done ===" << std::endl;
        if (!error) {
            socket_.async_read_some(
                    boost::asio::buffer(data_),
                    boost::bind(&session::handle_read, shared_from_this(),
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));
        }
    }
};

class server {
private:
    boost::asio::io_context &io_context_;
    stream_protocol::acceptor acceptor_;

public:
    server(boost::asio::io_context &io_context, const std::string &file)
            : io_context_(io_context),
              acceptor_(io_context, stream_protocol::endpoint(file)) {
        std::shared_ptr<session> new_session(new session(io_context_));
        std::cout << "server" << std::endl;
        acceptor_.async_accept(
                new_session->socket(),
                boost::bind(&server::handle_accept, this, new_session,
                            boost::asio::placeholders::error));
    }

    void handle_accept(std::shared_ptr<session> new_session,
                       const boost::system::error_code &error) {
        std::cout << "handle_accept" << std::endl;
        if (!error) {
            new_session->start();
        }
        new_session.reset(new session(io_context_));
        acceptor_.async_accept(
                new_session->socket(),
                boost::bind(&server::handle_accept, this, new_session,
                            boost::asio::placeholders::error));
    }
};

int main(int argc, char *argv[]) {
    std::remove(socket_path.data());
    std::cout << "Starting server on " << socket_path << std::endl;
    boost::asio::io_context io_context;
    server s(io_context, socket_path);
    io_context.run();

    return 0;
}