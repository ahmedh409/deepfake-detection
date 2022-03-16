// node.cpp
#include "node.h"
#include <cstdint>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>

Node::Node(int id) {
    this->_id = id;

    /*
    all of this (except loop) will eventually be moved or replaced
    this is a temporary and local way of creating a global node list
    */

    struct comm::comm_info* info = (struct comm::comm_info*) 
                                    malloc(sizeof(struct comm::comm_info));
    info->port_number = (int) DEFAULT_PORT_NUMBER + this->_id;

    // keep trying to setup a socket until it works
    while (comm::init(info) != 0) {
        sleep(1);
    }

    // create a new node in the contact list
    struct comm::node_contact_info mynode = {this->_id, info->port_number, true};

    try {
        // create the public file and write to it
        std::ofstream myfile;
        std::string filename = "./temp/node_list/" + std::to_string(this->_id) + ".txt";
        myfile.open(filename, std::fstream::out | std::fstream::trunc);
        myfile << this->_id << " " << info->port_number << " finished";
        myfile.close();
    } catch (...) {
        exit(1);
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
                    struct comm::node_contact_info* n = (comm::node_contact_info*)
                                                        malloc(sizeof(comm::node_contact_info));
                    n->id = std::stoi(words[0]);
                    n->port = std::stoi(words[1]);
                    this->node_ids.push_back(n->id);
                    this->node_map.insert(std::pair<int, comm::node_contact_info*>
                                            (n->id, n));
                    highest_node_found++;
                }
            }
        }
        std::cout << "Node " << this->_id << ", Nodes found: " << 
                     this->node_ids.size() << std::endl;
        if (this->_id == 10) {
            for (int i = 0; i < this->node_ids.size(); i++) {
                comm::node_contact_info* node = this->get_contact_info(this->node_ids[i]);
                std::cout << "Node " << this->node_ids[i] << ", Port : " << node->port << std::endl;
            }
        }
        sleep(2);
    }
}


// get a node's contact information from its ID
// since this is only 1 line, this would not be difficult to do each time
//  we need to get contact info, but this provides a nice abstraction
comm::node_contact_info* Node::get_contact_info(int id) {
    return this->node_map[id];
}
