#include <cstdint>
#include <vector>
#include "block.h"

class blockchain {
public:
    blockchain(uint32_t diff);

    void addBlock(block b_new);

    void display(void);

    // n_difficulty is a private variable for security reasons, display_diff is a public dummy variable used for output
    uint32_t display_diff;

private:
    uint32_t _n_difficulty;

    std::vector<block> _v_chain;

    block _getLastBlock() const;
};