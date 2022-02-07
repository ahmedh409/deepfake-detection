#include "blockchain.h"

blockchain::blockchain(uint32_t diff) {
    // constructor, uses a genesis block at index 0
    _v_chain.push_back(block(0, "genesis_block"));
    _n_difficulty = diff;
    display_diff = _n_difficulty;
}

void blockchain::addBlock(block b_new) {
    std::cout << "adding to blockchain, beginning mining sequence ->" << std::endl;
    b_new.s_prev_hash = _getLastBlock().getHash();
    b_new.mineBlock(_n_difficulty);
    _v_chain.push_back(b_new);
    std::cout << "\tblock mined: " << b_new.getHash() << std::endl;
    std::cout << "-> successfully added to blockchain!" << std::endl;
}

void blockchain::display(void) {
    std::cout << std::endl;
    for (int i = 0; i < _v_chain.size(); i++)
        std::cout << "[ B-" << i << ": \"" << _v_chain[i].data << "\" ]--->";
    std::cout << std::endl;
}

block blockchain::_getLastBlock() const {
    return _v_chain.back();
}