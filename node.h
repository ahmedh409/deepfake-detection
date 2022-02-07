// node.h

#include <cstdint>
using namespace std;

class Node {
public:
    
    Node(uint32_t id);

private:
    // some form of identification
    uint32_t _id;
    // need to implement some sort of digital signature scheme
};