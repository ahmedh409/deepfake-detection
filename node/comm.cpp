// comm.cpp
#include "comm.h"
#include <iostream>
#include <string>
// not sure how many of these are actually necessary
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <boost/asio.hpp>

#include <errno.h>
#include <string.h>
#include <stdio.h>
extern int errno ;

namespace comm {

/*
int init(comm_info* info) {
    int sockfd;     // socket file descriptor
    // create the socket
    //      AF_INET means IPv4 (rather than IPv6)
    //      SOCK_STREAM means TCP (rather than UDP)
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        // socket created unsuccessfully, do not proceed
        // could alternatively raise an error
        printf("Failed at socket creation\n");
        int errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
        return -1;
    }

    info->sockfd = sockfd;

    // create the socket address struct (in means internet)
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;      // type of address is IPv4
    addr.sin_port = htons(info->port_number);   // convert to the correctly ordered unsigned short
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // set IP to localhost

    // this is required to open the port back up quickly for rapid testing
    // this sets the REUSE ADDRESS option to 1 (on)
    int one = 1;
    setsockopt(info->sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    
    // bind the socket
    if (bind(info->sockfd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        // socket bound unsuccessfully, do not proceed
        // could alternatively raise an error
        printf("Failed at binding\n");
        int errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
        return -1;
    }

    return 0;
}
*/

// setup the TCP server
int init(comm_info* info) {
    // create the asio context
    boost::asio::io_context io_context;
    // create a TCP server
    
}

void listen_and_accept(comm_info* info) {
    // the socket listens for incoming connection requests
    // listen() is a non-blocking function,
    //      it puts the socket in a passive state so it is ready to accept
    int backlog_size = 2;   // number of requests to store while others are processed
    listen(info->sockfd, backlog_size);

    // accept() is a blocking function, so it will hang until a request comes
    // infinite accept loop
    while (true) {
        // create the struct to hold the requester's information
        struct sockaddr* client_address = (struct sockaddr*) malloc(sizeof(struct sockaddr_in));
        socklen_t address_len = sizeof(client_address);

        int client_sockfd = accept(info->sockfd, client_address, &address_len);

        std::cout << "AHHHHHHHHHH" << std::endl;

        if (client_sockfd < 0) {
            printf("Failed to accept incoming connection\n");
            delete client_address;
            continue;
        }

        std::cout << "AHHHHHHHHHH2" << std::endl;

        // create a message
        struct message* m = (struct message*) malloc(sizeof(struct message));
        std::cout << "wtf" << std::endl;
        m->type = 0;    // connection flag
        std::cout << "wtf2" << std::endl;
        m->sender = client_address;
        std::cout << "wtf3" << std::endl;
        //m->body.assign("");
        std::cout << "wtf4" << std::endl;

        std::cout << "AHHHHHHHHHH3" << std::endl;

        // add the message to the message queue
        info->message_queue_lock->lock();
        info->message_queue->push_back(m);
        info->message_queue_lock->unlock();



        std::cout << "AHHHHHHHHHH4" << std::endl;
    }
}

int initiate_connection(comm_info* info, node_contact_info* target) {
    struct sockaddr_in target_address;
    target_address.sin_family = AF_INET;
    target_address.sin_port = htons(target->port);
    target_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    //int successful = connect(info->send_sockfd, (struct sockaddr*) &target_address, sizeof(target_address));
    int successful = 1;
    if (successful < 0) {
        printf("Failed on establishing connection\n");
        int errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
        return -1;
    }
    target->connection_established = true;
    return successful;
}

int shutdown(comm_info* info) {
    return close(info->sockfd);
}

void send(std::string message) {
    std::cout << "Sending message: " << message << std::endl;
}

void recv() {
    std::cout << "Receiving message" << std::endl;
}

} // namespace comm