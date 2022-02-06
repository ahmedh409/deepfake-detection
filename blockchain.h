#include <cstdint>
#include <vector>
#include "block.h"

using namespace std;

class blockchain {
public:
    blockchain(uint32_t diff);

    void addBlock(block b_new);

    uint32_t display_diff;

private:
    uint32_t _n_difficulty;
    vector<block> _v_chain;

    block _getLastBlock() const;
};