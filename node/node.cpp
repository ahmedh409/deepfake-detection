// node.cpp
#include "node.h"
#include "comm.h"
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

    try {
        // create the public file and write to it
        std::ofstream myfile;
        std::string filename = "./temp/node_list/" + std::to_string(this->_id) + ".txt";
        myfile.open(filename, std::fstream::out | std::fstream::trunc);
        myfile << this->_id << " " << this->_id << " finished";
        myfile.close();
    } catch (...) {
        exit(1);
    }

    struct comm::comm_info* info = (struct comm::comm_info*) 
                                    malloc(sizeof(struct comm::comm_info));
    info->port_number = (int) DEFAULT_PORT_NUMBER + this->_id;
    printf("Id: %d, port: %d\n", this->_id, info->port_number);
    
    // keep trying to setup a socket until it works
    while (comm::init(info) != 0) {
        sleep(1);
    }
    this->loop();
}

void Node::loop() {
    // highest node id found and added to the list so far
    int highest_node_found = 0;

    for (int i = 0; i < 5; i++) {
        // need to find all files and read through them
        // starting at highest_node_found+1, try to find the nodes
        bool keep_going = true;
        for (int j = highest_node_found+1; keep_going; j++) {
            std::string filename = "./temp/node_list/" + std::to_string(j) + ".txt";
            std::ifstream node_file(filename);
            if (!node_file.good()) {
                keep_going = false;
                continue;
            }
            if (node_file.is_open()) {
                std::vector<std::string> words;
                std::string word;
                while (node_file >> word) {
                    words.push_back(word);
                }
                if (words.size() != 3) {
                    keep_going = false;
                    continue;
                }
                if (words[2] == "finished") {
                    NodeInfo n;
                    n.id = std::stoi(words[0]);
                    n.port = std::stoi(words[1]);
                    this->node_list.push_back(&n);
                    highest_node_found++;
                }
            }
        }
        std::cout << "Node " << this->_id << ", Nodes found: " << 
                     this->node_list.size() << std::endl;
        sleep(2);

        i;
    }
}
