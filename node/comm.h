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
    struct sockaddr* sender;
    std::string body;
};

// a data structure to store all information about the communication of a node
// passed into each function and manipulated, so the node maintains state
struct comm_info {
    int sockfd;
    int ip_address;     // probably shouldn't be an int
    int port_number;
    std::deque<message*>* message_queue;
    std::mutex* message_queue_lock;
};

struct node_contact_info {
    //int id;
    int port;
    struct sockaddr_in* address;
    bool connection_established;
};


// create and setup a socket
//int init(comm_info* info);

// setup and run TCP server to listen for connections and messages
int run_tcp_server(comm_info* info);

// listen for incoming connections and accept them
//void listen_and_accept(comm_info* info);

// establish a TCP connection as the client
int initiate_connection(comm_info* info, node_contact_info* target);

// close the socket
int shutdown(comm_info* info);

void send(std::string message);
void recv();

} // namespace comm

#endif