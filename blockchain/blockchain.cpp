#include "blockchain.h"

blockchain::blockchain(uint32_t diff) {
    // constructor, uses a genesis block at index 0
    _v_chain.push_back(block(0, "init"));
    _n_difficulty = diff;
    display_diff = _n_difficulty;
    num_block = 1;;
}

void blockchain::addBlock(block b_new) {
    std::cout << "adding to blockchain, beginning mining sequence ->" << std::endl;
    b_new.s_prev_hash = _getLastBlock().getHash();
    b_new.mineBlock(_n_difficulty);
    _v_chain.push_back(b_new);
    std::cout << "\tblock mined: " << b_new.getHash() << std::endl;
    std::cout << "-> successfully added to blockchain!" << std::endl;
    num_block++;
}

void blockchain::display(void) {
    std::cout << "Cryptographic algorithm used: SHA-256\nn_difficulty is set to " << display_diff << "; higher numbers take longer to hash\nMost of this is from a tutorial online, link commented in main.cpp\n" << std::endl;

    for (int i = 0; i < _v_chain.size(); i++)
        std::cout << "[ B-" << i << ": \"" << _v_chain[i].data << "\" ]--->";
    std::cout << std::endl;
}

block blockchain::search_chain(std::string hash) {
    for (int i = 1; i < _v_chain.size(); i++) {
        if (_v_chain[i].data == hash)
            return _v_chain[i];
    }
    return _v_chain[0];
}

block blockchain::_getLastBlock() const {
    return _v_chain.back();
}