// #define BOOST_ASIO_ENABLE_HANDLER_TRACKING
#include <array>
#include <boost/asio.hpp>
#include <boost/asio/read.hpp>
#include <boost/noncopyable.hpp>
#include <cstddef>
#include <iostream>

namespace ba = boost::asio;

struct talk_to_svr;
using client_ptr = std::shared_ptr<talk_to_svr>;

// *********************** GLOBALS ***********************

ba::io_service service;

// ******************** talk_to_server ********************

struct talk_to_svr : public std::enable_shared_from_this<talk_to_svr>, boost::noncopyable
{
private:
    ba::ip::tcp::socket sock_;
    bool started_ = false;
    std::string username_;
    constexpr static size_t max_msg = 1024;
    std::array<char, max_msg> read_buffer_;
    std::array<char, max_msg> write_buffer_;
public:
    static client_ptr start(ba::ip::tcp::endpoint ep, const std::string& username)
    {
        client_ptr new_client(new talk_to_svr(username));
        new_client->connect_and_begin(ep);
        return new_client;
    }
private:
    talk_to_svr(const std::string& username) : sock_(service), started_(true), username_(username) {}

    void connect_and_begin(ba::ip::tcp::endpoint ep)
    {
        sock_.async_connect(
            ep,
            [self = shared_from_this()](const boost::system::error_code& err)
            {
                if (err)
                {
                    std::cout << "[client.connect_and_begin.callback] err " << err.message() << std::endl;
                    return;
                }

                std::cout << "[client.connect_and_begin.callback] client connected" << std::endl;
                self->do_write(self->username_ + "_");
            });
    }

    void do_write(const std::string& msg)
    {
        if (!started_)
        {
            std::cout << "[client.do_write] writing msg=" << msg << std::endl;
            return;
        }

        std::copy(msg.begin(), msg.end(), write_buffer_.begin());
        std::cout << "[client.do_write] writing msg=" << msg << std::endl;
        sock_.async_write_some(
            ba::buffer(write_buffer_, msg.size()),
            [self = shared_from_this()](const boost::system::error_code& err, size_t bytes)
            {
                if (err)
                {
                    std::cout << "[client.do_write.callback] err " << err.message() << std::endl;
                    return;
                }

                self->do_read();
            });
    }

    void do_read()
    {
        if (!started_)
        {
            std::cout << "[client.do_read] client not started" << std::endl;
            return;
        }

        ba::async_read(
            sock_, ba::buffer(read_buffer_),
            [self = shared_from_this()](const boost::system::error_code& err, size_t bytes) -> size_t
            {
                if (err)
                {
                    std::cout << "[client.do_read.completion] error: " << err.message() << std::endl;
                    self->stop();
                    return 0; // Should return 0 to finalize curent async call
                }
                std::string msg(self->read_buffer_.begin(), self->read_buffer_.begin() + bytes);
                std::cout << "[client.do_read.completion]: " << msg << std::endl;

                bool end_symbol_found = msg.find('_') != std::string::npos;
                std::cout << "[client.do_read.completion] end_symbol_found=" << end_symbol_found << std::endl;

                // When this completion function returns 0, we consider the read operation complete;
                return !end_symbol_found;
            },
            [self = shared_from_this()](const boost::system::error_code& err, size_t bytes)
            {
                if (err)
                {
                    std::cout << "[client.do_read.callback] error" << err.message() << std::endl;
                }

                std::string msg(self->read_buffer_.begin(), self->read_buffer_.begin() + bytes);
                std::cout << "[client.do_read.callback]: read full msg=" << msg << std::endl;
            });
    }

    void stop()
    {
        if (!started_)
            return;
        std::cout << "[client.stop]" << std::endl;
        started_ = false;
        sock_.close();
    }
};

int main()
{
    // Create several clients and connect them to the server
    ba::ip::tcp::endpoint ep(ba::ip::address::from_string("127.0.0.1"), 8001);
    char* names[] = {"John", "James", "Lucy", "Tracy", "Frank", "Abby", 0};
    for (char** name = names; *name; ++name)
    {
        talk_to_svr::start(ep, *name);
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
    }

    service.run();
}
