// node.cpp
#include "node.h"
#include <cstdint>
#include <vector>

std::vector<uint32_t> Node::node_list;

Node::Node(uint32_t id) {
    this->_id = id;
    this->node_list.push_back(this->_id);
}