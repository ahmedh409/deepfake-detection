#include "blockchain.h"

blockchain::blockchain(uint32_t diff) {
    // constructor, uses a genesis block at index 0
    _v_chain.push_back(block(0, "Genesis Block"));
    _n_difficulty = diff;
    display_diff = _n_difficulty;
}

void blockchain::addBlock(block b_new) {
    cout << "adding to blockchain, beginning mining sequence ->" << endl;
    b_new.s_prev_hash = _getLastBlock().getHash();
    b_new.mineBlock(_n_difficulty);
    _v_chain.push_back(b_new);
    cout << "\tBlock mined: " << b_new.getHash() << endl;
    cout << "-> successfully added to blockchain!" << endl;
}

block blockchain::_getLastBlock() const {
    return _v_chain.back();
}