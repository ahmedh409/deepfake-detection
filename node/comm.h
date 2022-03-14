// comm.h
// Comm: a project library developed for communication functionality
#include <string>

/*
This is a stateless library. This means all state relating to communication,
such as socket information, number of messages sent/received, etc., is
handled elsewhere, such as by the Node class. These functions are meant to
operate solely on the inputs provided to them.
*/

namespace comm {

// a data structure to store all information about the communication of a node
// passed into each function and manipulated, so the node maintains state
struct comm_info {
    int ip_address;     // probably shouldn't be an int
    int port_number;
    // message buffer
    // message buffer lock
};


// create and setup a socket
bool init_socket(comm_info &info);

void send(std::string message);
void recv();

} // namespace comm