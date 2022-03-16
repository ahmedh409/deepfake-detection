// node.h
#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <vector>
#include <map>
#include "comm.h"

class Node {
public:
    
    Node(int id);

private:
    // form of identification
    int _id;

    void loop();

    std::vector<int> node_ids;

    // map of node IDs to their contact information
    std::map<int, comm::node_contact_info*> node_map;

    // get a node's contact information from its ID
    comm::node_contact_info* get_contact_info(int id);

    // need to implement some sort of digital signature scheme
    // here
};

#endif