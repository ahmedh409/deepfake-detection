// node.cpp
#include "node.h"
#include <cstdint>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>

Node::Node(int id) {
    this->_id = id;

    // setup communications
    this->setup_communications();
    // publish node information for other nodes to see

    /*
    all of this (except loop) will eventually be moved or replaced
    this is a temporary and local way of creating a global node list
    */
    // create a new node in the contact list
    struct comm::node_contact_info mynode = {this->comm_info.port_number, NULL, true};

    try {
        // create the public file and write to it
        std::ofstream myfile;
        std::string filename = "./temp/node_list/" + std::to_string(this->_id) + ".txt";
        myfile.open(filename, std::fstream::out | std::fstream::trunc);
        myfile << this->_id << " " << this->comm_info.port_number << " finished";
        myfile.close();
    } catch (...) {
        exit(1);
    }



    this->loop();
}

void Node::setup_communications() {
    this->comm_info.port_number = (int) DEFAULT_PORT_NUMBER + this->_id;
    this->comm_info.message_queue = &this->message_queue;
    this->comm_info.message_queue_lock = &this->message_queue_lock;

    // keep trying to setup a socket until it works
    while (comm::init(&this->comm_info) != 0) {
        sleep(1);
    }

    // create a thread to listen for incoming messages and connections
    std::thread listener_thread(comm::listen_and_accept, &this->comm_info);
    // detaching the thread allows it to continue indefinitely and independently
    listener_thread.detach();
}

// get a node's contact information from its ID
// since this is only 1 line, this would not be difficult to do each time
//      we need to get contact info, but this provides a nice abstraction
comm::node_contact_info* Node::get_contact_info(int id) {
    return this->node_contact_map[id];
}

// handle all incoming messages off of the message queue
void Node::process_messages() {
    this->message_queue_lock.lock();
    while (!this->message_queue.empty()) {
        std::cout << this->message_queue.empty() << std::endl;
        // pop the first message off the queue
        comm::message* m = this->message_queue.front();
        this->message_queue.pop_front();

        // act on the message, depending on the type of message
        switch (m->type) {
            // connection established
            case 0 :
                {
                    // add the connection to the map
                    struct sockaddr_in* address = (struct sockaddr_in*) m->sender;
                    int port = address->sin_port;
                    std::cout << "portttt : " << port << std::endl;
                    comm::node_contact_info* info = this->get_contact_info(port);
                    if (info == NULL) {
                        printf("NULL pointer on connection establishment\n");
                        break;
                    }
                    info->address = address;
                    info->connection_established = true;
                    printf("Connection established\n");
                    break;
                }
            // message
            case 1 :
                printf("New message: \n");
                break;
        }

        // delete the message from the heap
        delete m;
    }
    this->message_queue_lock.unlock();
}

void Node::loop() {
    sleep(2);
    // highest node id found and added to the list so far
    
    int highest_node_found = 0;
    
    for (int i = 0; i < 5; i++) {
        this->process_messages();
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
                    comm::node_contact_info* n = (comm::node_contact_info*)
                                                    malloc(sizeof(comm::node_contact_info));
                    //n->id = std::stoi(words[0]);
                    n->port = std::stoi(words[1]);
                    this->node_ports.push_back(n->port);
                    this->node_contact_map.insert(std::pair<int, comm::node_contact_info*>
                                            (n->port, n));
                    std::cout << this->_id << "count: " << this->node_contact_map.size() << std::endl;
                    std::cout << this->_id << "port : " << n->port << std::endl;
                    highest_node_found++;
                }
            }
        }
        std::cout << "Node " << this->_id << ", Nodes found: " << 
                     this->node_ports.size() << std::endl;
        if (this->_id >= 1) {
            for (int i = 0; i < this->node_ports.size(); i++) {
                comm::node_contact_info* node = this->get_contact_info(this->node_ports[i]);
                if (this->comm_info.port_number == node->port) {
                    continue;
                }
                std::cout << "Node " << this->node_ports[i] << ", Port : " << node->port <<
                            ", Connected : " << node->connection_established << std::endl;
            }
        }

        for (int i = 0; i < this->node_ports.size(); i++) {
            comm::node_contact_info* node = this->get_contact_info(this->node_ports[i]);
            // if this node's port is higher, skip
            if (this->comm_info.port_number >= node->port) {
                continue;
            }
            if (node->connection_established) {
                continue;
            }
            std::cout << "This port: " << this->comm_info.port_number << ", other port: " << node->port << std::endl;
            // initiate connection
            std::cout << "Success? " << comm::initiate_connection(&this->comm_info, node) << std::endl;
        }

        if (this->_id == 2) {
            std::cout << "222222" << std::endl;
        }

        sleep(2);
    }
    
}
