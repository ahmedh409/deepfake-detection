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

#include <errno.h>
#include <string.h>
#include <stdio.h>
extern int errno ;

namespace comm {

int init(comm_info* info) {
    int sockfd;     // socket file descriptor
    // create the socket
    //  AF_INET means IPv4 (rather than IPv6)
    //  SOCK_STREAM means TCP (rather than UDP)
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
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
    
    // bind the socket
    if (bind(sockfd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        // socket bound unsuccessfully, do not proceed
        // could alternatively raise an error
        printf("Failed at binding\n");
        int errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
        return -1;
    }

    // listening is handled by a different function
    listen(sockfd, 0);

    return 0;
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