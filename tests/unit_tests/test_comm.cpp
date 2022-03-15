#include "node/comm.cpp"

// create a socket
TEST(test_socket_creation) {
    // create the information struct
    struct comm::comm_info info;
    info.port_number = (int) DEFAULT_PORT_NUMBER;

    // create the socket
    // return code should be zero
    int socket_creation_status = comm::init(&info);
    ASSERT_TRUE(socket_creation_status == 0);

    // close the socket
    // return code should be zero
    int socket_destruction_status = comm::shutdown(&info);
    ASSERT_TRUE(socket_destruction_status == 0);
}