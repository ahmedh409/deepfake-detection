// node.cpp
#include "node.h"
#include <cstdint>
#include <vector>
#include <unistd.h>
#include <iostream>

std::vector<uint32_t> Node::node_list;

Node::Node(uint32_t id) {
    this->_id = id;
    this->node_list.push_back(this->_id);

    this->loop();
}

void Node::loop() {
    for (int i = 0; i < 10; i++) {
        std::cout << "Node " << this->_id << ", iteration " << i + 1 << std::endl;
        sleep(2);
    }
}
