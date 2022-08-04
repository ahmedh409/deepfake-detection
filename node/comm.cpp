// comm.cpp
#include "comm.h"
#include <iostream>
#include <string>

#include <boost/asio.hpp>
using boost::asio::ip::tcp;


namespace comm {

// run the TCP server
void run_tcp_server(comm_info* info) {
    try {
        // create the asio context
        boost::asio::io_context io_context;

        // create the acceptor which will listen on the port for incoming connections
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), info->port_number));
        boost::system::error_code ec;
        acceptor.set_option(tcp::acceptor::reuse_address(true), ec);

        for (;;) {
            // wait for a connection and bind it to a socket
            std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_context);
            acceptor.accept(*socket);

            // add a message to the queue indicating a new connection
            if (!(*socket).is_open()) {
                std::cout << "Error: socket failed to open" << std::endl;
                continue;
            }
            
            boost::asio::streambuf sb;
            boost::system::error_code ec;
            boost::asio::read(*socket, sb, boost::asio::transfer_exactly(5), ec);
            std::string message(boost::asio::buffers_begin(sb.data()), 
                                boost::asio::buffers_begin(sb.data()) + sb.size());
            
            if (ec) {
                std::cout << "status: " << ec.message() << "\n";
                break;
            }

            struct message m = {0, socket, std::stoi(message), ""};
            info->message_queue_lock->lock();
            info->message_queue->push_back(m);
            info->message_queue_lock->unlock();
        }
    } catch (std::exception& e) {
        std::cout << "----- SERVER CRASHED -----" << std::endl;
        std::cerr << e.what() << std::endl;
    }
}

// connect to a TCP server
int initiate_connection(comm_info* info, node_contact_info* target) {
    try {
        // create the asio context
        boost::asio::io_context io_context;

        // resolve the address to an endpoint
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints =
            resolver.resolve("127.0.0.1", std::to_string(target->port));
    
        // make the connection and bind it to a socket
        std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_context);
        boost::asio::connect(*socket, endpoints);

        // this is necessary to make sure the server has had time to initiate a read
        sleep(1);

        // send ID to finish handshake
        boost::system::error_code ec;
        boost::asio::write(*socket, boost::asio::buffer(std::to_string(info->port_number)), ec);
        if (ec) {
            std::cout << "status: " << ec.message() << "\n";
            return -1;
        }

        struct message m = {0, socket, target->port, ""};
        info->message_queue_lock->lock();
        info->message_queue->push_back(m);
        info->message_queue_lock->unlock();

    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}

// convert a packet into a string representation to be sent over the network
std::string packet_to_string(struct packet p) {
    std::string size = "";
    if (p.size <= 999) {
        size += "0";
    }
    if (p.size <= 99) {
        size += "0";
    }
    if (p.size <= 9) {
        size += "0";
    }
    size += std::to_string(p.size);
    return (size + p.message);
}

// convert string message into packet and send
int send(std::shared_ptr<tcp::socket> socket, std::string message) {
    struct packet p = {(int) message.size(), message};
    if (p.size > 9999) {
        return -1;
    }
    socket->send(boost::asio::buffer(packet_to_string(p)));
    return 0;
}

void recv(comm_info* info, std::shared_ptr<tcp::socket> socket, int port) {
    for (;;) {
        if (socket->available() == 0) {
            continue;
        }

        // read the first 4 bytes containing the size of the incoming message
        boost::asio::streambuf sb;
        boost::system::error_code ec;

        boost::asio::read(*socket, sb, boost::asio::transfer_exactly(4), ec);
        std::string message_size(boost::asio::buffers_begin(sb.data()), 
                                 boost::asio::buffers_begin(sb.data()) + sb.size());
        int size = std::stoi(message_size);


        // read the message body
        boost::asio::read(*socket, sb, boost::asio::transfer_exactly(size), ec);
        std::string message_body(boost::asio::buffers_begin(sb.data()) + 4, 
                                 boost::asio::buffers_begin(sb.data()) + sb.size());
        

        // add the message to the message queue
        struct message m = {1, NULL, port, message_body};
        info->message_queue_lock->lock();
        info->message_queue->push_back(m);
        info->message_queue_lock->unlock();
    }
}

} // namespace comm