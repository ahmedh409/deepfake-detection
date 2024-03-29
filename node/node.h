// node.h
#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <vector>
#include <fstream>
#include <deque>
#include <map>
#include <mutex>
#include "comm.h"
#include "../blockchain/block.h"

#include <boost/asio.hpp>
using boost::asio::ip::tcp;


class Node {
public:
    // constructor
    Node(int id);
    // destructor
    // we currently have memory leaks, fix this with destructor

private:
    int highest_node_found;

    // form of identification
    int _id;
    struct comm::comm_info comm_info;
    struct comm::node_contact_info my_contact_info;

    /*****
    Initialization tasks
    *****/
    void setup_communications();
    void publish_information();

    // list of all node IDs, used to index into the map
    std::vector<int> node_ids;
    // map of node IDs to their contact information
    std::map<int, comm::node_contact_info*> node_contact_map;

    // get a node's contact information from its ID
    comm::node_contact_info* get_contact_info(int id);

    // find all the other nodes
    void find_other_nodes();

    /*****
    Handle command-line input
    *****/
    typedef struct {
        std::deque<std::string> input_queue;
        std::mutex input_queue_lock;
    } input_information;

    input_information input_info;
    static void read_input(input_information* input_info);
    void handle_input();

    /*****
    Communication
    *****/
    void send(int target_id, std::string message);
    // send message to all nodes
    void broadcast(std::string message);

    /*****
    Process incoming messages
    *****/
    // message queue
    std::deque<comm::message> message_queue;
    // lock for the message queue
    std::mutex message_queue_lock;
    // submethod of the main loop to handle all messages on the message queue
    void process_messages();

    /*****
    Blockchain
    *****/
    // the file storing the blockchain
    //std::ofstream blockchain_file;
    std::vector<std::string> blockchain;    // each element is a hash
    // convert an image file (specified by path) to a hash, returns "" if it fails
    std::string hash_image(std::string filename);
    // add the hash to the personal chain and broadcast to all other node
    int add_hash_to_chain(std::string hash);
    // search the chain for a specific hash
    bool search_chain(std::string hash);

    /*****
    Loop
    *****/
    // main loop, runs indefinitely
    void loop();

};

#endif