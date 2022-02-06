#include "blockchain.h"

blockchain::blockchain() {
    // constructor, uses a genesis block at index 0
    _v_chain.push_back(block(0, "Genesis Block"));
    _n_difficulty = 3;
}

void blockchain::addBlock(block b_new) {
    b_new.s_prev_hash = _getLastBlock().getHash();
    b_new.mineBlock(_n_difficulty);
    _v_chain.push_back(b_new);
}

block blockchain::_getLastBlock() const {
    return _v_chain.back();
}