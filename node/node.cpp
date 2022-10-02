// node.cpp
#include "node.h"
#include <cstdint>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>

#include "../hashing/phash.h"

#include <boost/asio.hpp>
using boost::asio::ip::tcp;


Node::Node(int id) {
    this->_id = id;

    // setup communications
    this->setup_communications();
    // publish node information for other nodes to see
    this->publish_information();

    // highest node id found and added to the list so far
    this->highest_node_found = -1;

    // setup the thread to listen for external input (from the user/simulator)
    std::thread input_thread(&this->read_input, &this->input_info);
    input_thread.detach();

    // allow nodes to publish their information
    sleep(2);

    for (int i = 0; i < 5; i++) {
        this->loop();
    }
}

void Node::publish_information() {
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
}

void Node::setup_communications() {
    this->comm_info.port_number = (int) DEFAULT_PORT_NUMBER + this->_id;
    this->comm_info.message_queue = &this->message_queue;
    this->comm_info.message_queue_lock = &this->message_queue_lock;

    // create a thread to listen for incoming messages and connections
    std::thread listener_thread(comm::run_tcp_server, &this->comm_info);
    // detaching the thread allows it to continue indefinitely and independently
    listener_thread.detach();
}

// constantly read from standard input and add input to a command queue
// any check to cin blocks until input is ready, so this runs in a separate thread
void Node::read_input(input_information* input_info) {
    for (;;) {
        std::string command;
        getline(std::cin, command);
        if (command == "") {
            continue;
        }

        // add the command to the queue to be processed
        input_info->input_queue_lock.lock();
        input_info->input_queue.push_back(command);
        input_info->input_queue_lock.unlock();
    }
}

/* handle command-line input, the valid options are:
    * add [image_file (string)]
    * search [hash (string)]
    * send [target_id (int)] [message (string)]
*/
void Node::handle_input() {
    this->input_info.input_queue_lock.lock();

    // if there is input available, pop the first command off the queue
    while (!this->input_info.input_queue.empty()) {
        std::string command = this->input_info.input_queue.front();
        this->input_info.input_queue.pop_front();

        // break the string into words using " " as a delimeter
        std::vector<std::string> command_words;
        size_t pos = 0;
        std::string word;
        while ((pos = command.find(" ")) != std::string::npos) {
            word = command.substr(0, pos);
            command_words.push_back(word);
            command.erase(0, pos + 1);
        }
        command_words.push_back(command);

        // handle each type of input
        std::string command_type = command_words[0];
        if (command_type == "add") {
            std::string hash = this->hash_image(command_words[1]);
            this->add_hash_to_chain(hash);
        } else if (command_type == "search") {
            this->search_chain(command_words[1]);
            // need a way of actually passing the output back to the simulator
        } else if (command_type == "send") {
            int target_id = std::stoi(command_words[1]);
            this->send(target_id, command_words[2]);
        }

    }

    this->input_info.input_queue_lock.unlock();
}

// get a node's contact information from its ID
// since this is only 1 line, this would not be difficult to do each time
//      we need to get contact info, but this provides a nice abstraction
comm::node_contact_info* Node::get_contact_info(int id) {
    return this->node_contact_map[id];
}

void Node::send(int target_id, std::string message) {
    comm::node_contact_info* target = this->get_contact_info(target_id);
    if ((target == NULL)) {
        return;
    }
    comm::send(target->socket, message);
}

// send message to all nodes
void Node::broadcast(std::string message) {
    for (int i = 0; i < this->node_ids.size(); i++) {
        this->send(this->node_ids[i], message);
    }
}

// handle all incoming messages off of the message queue
void Node::process_messages() {
    this->message_queue_lock.lock();
    while (!this->message_queue.empty()) {
        // pop the first message off the queue
        comm::message m = this->message_queue.front();
        this->message_queue.pop_front();

        // act on the message, depending on the type of message
        switch (m.type) {
            // connection established
            case 0 :
                {
                    // add the connection to the map
                    std::shared_ptr<tcp::socket> socket = m.socket;
                    int port = m.id;
                    comm::node_contact_info* info = this->get_contact_info(port);
                    if (info == NULL) {
                        printf("NULL pointer on connection establishment\n");
                        break;
                    }
                    info->socket = socket;
                    info->connection_established = true;
                    
                    // create a receiving thread to scan for new messages
                    std::thread receiver_thread(comm::recv, &this->comm_info, socket, port);
                    // detaching the thread allows it to continue indefinitely and independently
                    receiver_thread.detach();
                    break;
                }
            // message
            case 1 :
                {
                    // hash received
                    this->blockchain.push_back(m.body);
                    std::string filename = "./temp/blockchain/" + std::to_string(this->_id) + ".txt";
                    std::ofstream blockchain_file;
                    blockchain_file.open(filename, std::fstream::out | std::fstream::trunc);
                    blockchain_file << m.body << std::endl;
                    blockchain_file.close();

                    break;
                }
        }
    }
    this->message_queue_lock.unlock();
}

void Node::find_other_nodes() {
    // need to find all files and read through them
    // starting at highest_node_found+1, try to find the nodes
    bool keep_going = true;
    for (int j = this->highest_node_found+1; keep_going; j++) {
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
                comm::node_contact_info* node = (comm::node_contact_info*)
                                                malloc(sizeof(comm::node_contact_info));
                node->port = std::stoi(words[1]);

                // skip current node
                if (node->port == this->comm_info.port_number) {
                    this->highest_node_found++;
                    continue;
                }

                this->node_ids.push_back(node->port);
                this->node_contact_map.insert(std::pair<int, comm::node_contact_info*>
                                             (node->port, node));
                this->highest_node_found++;
            }
        }
    }
}

// convert an image file (specified by path) to a hash, returns "" if it fails
std::string Node::hash_image(std::string filename) {
    return hash::generate_phash(filename);
}

// add the hash to the personal chain and broadcast to all other node
int Node::add_hash_to_chain(std::string hash) {
    // add the hash to the personal blockchain
    this->blockchain.push_back(hash);
    // broadcast the hash to all nodes
    this->broadcast(hash);

    std::string filename = "./temp/blockchain/" + std::to_string(this->_id) + ".txt";
    std::ofstream blockchain_file;
    blockchain_file.open(filename, std::fstream::out | std::fstream::trunc);
    blockchain_file << hash << std::endl;
    blockchain_file.close();

    return 1;
}

// search the chain for a specific hash
bool Node::search_chain(std::string hash) {
    for (std::string s : this->blockchain) {
        if (s == hash) {
            return true;
        }
    }
    return false;
}

void Node::loop() {
    this->process_messages();
    this->find_other_nodes();
    this->handle_input();

    int num_connections = 0;
    for (int i = 0; i < this->node_ids.size(); i++) {
        comm::node_contact_info* node = this->get_contact_info(this->node_ids[i]);
        if (node->connection_established) {
            num_connections++;
        }
    }
    std::cout << "Node " << this->_id << " connections: " << num_connections << " / " <<
            this->node_ids.size() << std::endl;

    // attempt to connect to other nodes
    for (int i = 0; i < this->node_ids.size(); i++) {
        comm::node_contact_info* node = this->get_contact_info(this->node_ids[i]);

        // if this node's port is higher, skip
        if (this->comm_info.port_number >= node->port) {
            continue;
        }

        // if connection is already established, don't try to connect again
        if (node->connection_established) {
            continue;
        }

        // initiate connection
        comm::initiate_connection(&this->comm_info, node);
    }

    sleep(2);

}
