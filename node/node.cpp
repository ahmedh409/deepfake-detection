// node.cpp
#include "node.h"
#include <cstdint>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

Node::Node(uint32_t id) {
    this->_id = id;

    /*
    all of this (except loop) will eventually be moved or replaced
    this is a temporary and local way of creating a global node list
    */
    // create a new node in the contact list
    struct NodeInfo mynode = {(int) this->_id, (int) this->_id};
    this->node_list.push_back(&mynode);

    // create the public file and write to it
    std::ofstream myfile;
    std::string filename = "./temp/node_list/" + std::to_string(this->_id) + ".txt";
    myfile.open(filename, std::fstream::out | std::fstream::trunc);
    myfile << this->_id << " " << this->_id << " finished";
    myfile.close();

    this->loop();
}

void Node::loop() {
    for (int i = 0; i < 1; i++) {
        // need to find all files and read through them
        std::cout << "Node " << this->_id << ", iteration " << i + 1 << std::endl;
        sleep(2);
    }
}
