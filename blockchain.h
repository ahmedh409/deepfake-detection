#include <cstdint>
#include <vector>
#include "block.h"

using namespace std;

class blockchain {
public:
    blockchain();

    void addBlock(block b_new);

private:
    uint32_t _n_difficulty;
    vector<block> _v_chain;

    block _getLastBlock() const;
};