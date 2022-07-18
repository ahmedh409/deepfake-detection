// this file defines and implements a TCP server
// it is an hpp file to denote that it's a header only class

// this follows from the Boost tutorial on an asynchronous TCP server

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

namespace comm {

class tcp_connection
    : public boost::enable_shared_from_this<tcp_connection>
{
public:
    typedef boost::shared_ptr<tcp_connection> pointer;

    static pointer create(boost::asio::io_context& io_context)
    {
        return pointer(new tcp_connection(io_context));
    }

    tcp::socket& socket()
    {
        return socket_;
    }

    void start()
    {
        std::cout << "CONNECTION RECEIVED AND HANDLED YAYYY" << std::endl;
        /*
        message_ = "";

        boost::asio::async_write(socket_, boost::asio::buffer(message_),
            boost::bind(&tcp_connection::handle_write, shared_from_this(),
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
        */
    }

private:
    tcp_connection(boost::asio::io_context& io_context)
      : socket_(io_context)
    {
    }

    void handle_write(const boost::system::error_code& /*error*/,
          size_t /*bytes_transferred*/)
    {
        std::cout << "MESSAGE RECEIVED" << std::endl;
    }

    tcp::socket socket_;
    std::string message_;
};

class tcp_server {

public:
    // constructor, creates the server
    tcp_server(boost::asio::io_context& io_context, int port_number)
        : io_context_(io_context),
          acceptor_(io_context, tcp::endpoint(tcp::v4(), port_number))
    {
        start_accept();
    }

private:

    void start_accept() {
        tcp_connection::pointer new_connection = tcp_connection::create(io_context_);
        acceptor_.async_accept(new_connection->socket(),
            boost::bind(&tcp_server::handle_accept, this, new_connection,
            boost::asio::placeholders::error));
        std::cout << "BEGINNING ACCEPT LOOP" << std::endl;
    }

    void handle_accept(tcp_connection::pointer new_connection,
                        const boost::system::error_code& error) {
        if (!error) {
            new_connection->start();
        }

        std::cout << "NEW CONNECTION HANDLED" << std::endl;

        // write to the socket
        std::string message = "M";
        boost::system::error_code ignored_error;
        //boost::asio::write(socket, boost::asio::buffer(message),
        //    boost::asio::transfer_all(), ignored_error);

        // the connection has been handled
        // reenter the asynchronous accept state
        start_accept();
    }

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;

};

} // namespace comm
