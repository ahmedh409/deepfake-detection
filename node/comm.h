// comm.h
// Comm: a project library developed for communication functionality
#ifndef COMM_H
#define COMM_H

#include <string>
#include <deque>
#include <mutex>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#define DEFAULT_PORT_NUMBER 12829

/*
This is a stateless library. This means all state relating to communication,
such as socket information, number of messages sent/received, etc., is
handled elsewhere, such as by the Node class. These functions are meant to
operate solely on the inputs provided to them.
*/

namespace comm {

struct message {
    // 0 - connection established
    // 1 - message received from established connection
    int type;
    std::shared_ptr<tcp::socket> socket;
    int id;
    std::string body;
};

// the data structure that gets sent across the network
struct packet {
    // the size in bytes of the remaining message
    int size;
    std::string message;
};

// a data structure to store all information about the communication of a node
// passed into each function and manipulated, so the node maintains state
struct comm_info {
    int port_number;
    std::deque<message>* message_queue;
    std::mutex* message_queue_lock;
};

struct node_contact_info {
    int port;
    std::shared_ptr<tcp::socket> socket;
    bool connection_established;
};


// setup and run TCP server to listen for connections and messages
void run_tcp_server(comm_info* info);

// establish a TCP connection as the client
int initiate_connection(comm_info* info, node_contact_info* target);


// convert a packet into a string representation to be sent over the network
std::string packet_to_string(struct packet p);

// send a message (called by node.cpp)
// convert string message into packet and send
int send(std::shared_ptr<tcp::socket> socket, std::string message);
// infinite loop to listen for messages on a socket (runs as a separate thread)
void recv(comm_info* info, std::shared_ptr<tcp::socket> socket, int port);

} // namespace comm

#endif