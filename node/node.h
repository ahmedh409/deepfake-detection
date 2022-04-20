// node.h
#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <vector>
#include <deque>
#include <map>
#include <mutex>
#include "comm.h"

class Node {
public:
    // constructor
    Node(int id);
    // destructor
    // we currently have memory leaks, fix this with destructor

private:
    // form of identification
    int _id;
    struct comm::comm_info comm_info;
    struct comm::node_contact_info my_contact_info;

    /*****
    Initialization tasks
    *****/
    void setup_communications();

    // list of all node IDs, used to index into the map
    std::vector<int> node_ports;//node_ids;
    // map of node IDs to their contact information
    std::map<int, comm::node_contact_info*> node_contact_map;

    // get a node's contact information from its ID
    comm::node_contact_info* get_contact_info(int id);

    /*****
    Process incoming messages
    *****/
    // message queue
    std::deque<comm::message*> message_queue;
    // lock for the message queue
    std::mutex message_queue_lock;
    // submethod of the main loop to handle all messages on the message queue
    void process_messages();

    // main loop, runs indefinitely
    void loop();

    // need to implement some sort of digital signature scheme
    // here
};

#endif