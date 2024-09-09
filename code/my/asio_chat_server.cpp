// #define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <boost/asio.hpp>
#include <boost/asio/read.hpp>
#include <boost/noncopyable.hpp>
#include <cassert>
#include <iostream>

namespace ba = boost::asio;

struct talk_to_client;
using client_ptr = std::shared_ptr<talk_to_client>;

// *********************** GLOBALS ***********************

ba::io_service service;
ba::ip::tcp::acceptor acceptor(service, ba::ip::tcp::endpoint(ba::ip::tcp::v4(), 8001)); // Listen on port 8001

// ******************** talk_to_client ********************

struct talk_to_client : public std::enable_shared_from_this<talk_to_client>, boost::noncopyable
{
private:
    ba::ip::tcp::socket sock_;
    bool started_ = false;
    constexpr static size_t max_msg = 1024;
    std::array<char, max_msg> read_buffer_;
    std::array<char, max_msg> write_buffer_;
public:
    // Factory method. make_shared is not used because ctor is private
    static client_ptr create() { return client_ptr(new talk_to_client()); }
public: // public Interface
    ba::ip::tcp::socket& sock() { return sock_; }
    void start_with_read()
    {
        started_ = true;
        do_read(); // first, we wait for client to login
    }
private:
    // ctor is private, to make not possible to create object on stack
    talk_to_client() : sock_(service), started_(false) {}

    void do_read()
    {
        // shared_from_this() is used to extend the lifetime of the object
        // and buffers until the asynchronous operation completes
        ba::async_read(
            sock_, ba::buffer(read_buffer_),
            [self = shared_from_this()](const boost::system::error_code& err, size_t bytes) -> size_t
            {
                if (err)
                {
                    std::cout << "[server.do_read.completion] error: " << err.message() << std::endl;
                    self->stop();
                    return 0; // Should return 0 to finalize curent async call
                }
                std::string msg(self->read_buffer_.begin(), self->read_buffer_.begin() + bytes);
                std::cout << "[server.do_read.completion] msg=`" << msg << "`" << std::endl;

                bool end_symbol_found = msg.find('_') != std::string::npos;
                std::cout << "[server.do_read.completion] end_symbol_found=" << end_symbol_found << std::endl;

                // When this completion function returns 0, we consider the read operation complete;
                return !end_symbol_found;
            },
            [self = shared_from_this()](const boost::system::error_code& err, size_t bytes)
            {
                if (err)
                {
                    std::cout << "[server.do_read.callback] client read error: " << err.message() << std::endl;
                    self->stop();
                }

                if (!self->started_)
                {
                    std::cout << "[server.do_read.callback] error: client not started" << std::endl;
                    return;
                }

                // process the msg
                std::string msg(self->read_buffer_.begin(), self->read_buffer_.begin() + bytes);
                std::cout << "[server.do_read.callback] read msg=" << msg << std::endl;

                self->do_write(msg);
            });
    }

    void do_write(const std::string& msg)
    {
        std::string hello_msg = "Hello " + msg;
        std::copy(hello_msg.begin(), hello_msg.end(), write_buffer_.begin());
        sock_.async_write_some(
            ba::buffer(write_buffer_, hello_msg.size()),
            [self = shared_from_this()](const boost::system::error_code& err, size_t bytes)
            {
                if (err)
                {
                    std::cout << "[server.do_write.callback] error " << err.message() << std::endl;
                }

                std::cout << "[server.do_write.callback] message sent" << std::endl;
            });
    }

    void stop()
    {
        if (!started_)
            return;
        std::cout << "[server.stop]" << std::endl;
        started_ = false;
        sock_.close();
    }
};

void handle_accept(client_ptr client, const boost::system::error_code& err)
{
    std::cout << "[server.handle_accept] client connected" << std::endl;
    client->start_with_read();
    client_ptr new_client_for_accept = talk_to_client::create();
    acceptor.async_accept(new_client_for_accept->sock(), std::bind_front(handle_accept, new_client_for_accept));
}

int main()
{
    std::cout << "[server] started" << std::endl;
    client_ptr new_client_for_accept = talk_to_client::create();
    std::cout << "[server] waiting for new connections" << std::endl;
    acceptor.async_accept(new_client_for_accept->sock(), std::bind_front(handle_accept, new_client_for_accept));
    service.run();
    std::cout << "[server] stopped" << std::endl;
}