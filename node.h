// node.h
#include <cstdint>
#include <vector>

class Node {
public:
    
    Node(uint32_t id);

    static std::vector<uint32_t> node_list;

private:
    // form of identification
    uint32_t _id;

    // need to implement some sort of digital signature scheme
    // here
};