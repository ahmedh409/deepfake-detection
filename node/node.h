// node.h
#include <cstdint>
#include <vector>

struct NodeInfo {
    int id;
    int port;
};

class Node {
public:
    
    Node(uint32_t id);

    std::vector<struct NodeInfo*> node_list;

private:
    // form of identification
    uint32_t _id;

    void loop();

    // need to implement some sort of digital signature scheme
    // here
};