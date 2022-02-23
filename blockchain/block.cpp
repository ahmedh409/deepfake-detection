#include <sstream>
#include "block.h"
#include "sha256.h"

block::block(uint32_t n_index_in, const std::string &s_data_in) : _n_index(n_index_in), _s_data(s_data_in) {
    _n_nonce = -1;
    _t_time = time(nullptr);
    data = _s_data;
}

std::string block::getHash() {
    return _s_hash;
}

void block::mineBlock(uint32_t n_difficulty) {
    // create string array with 1 more value than spec'd in n_difficulty
    char cstr[n_difficulty + 1];
    
    // fill array with zeroes, add string terminator character
    std::cout << "\t...filling hash array with zeroes and performing conversions...";
    for (uint32_t i = 0; i < n_difficulty; ++i) cstr[i] = '0';
    cstr[n_difficulty] = '\0';
    std::string str(cstr); // convert to standard string 
    std::cout << "DONE\n\t...calculating SHA-256 hash...";

    // do-whiles run at least once (exit control loop)
    do {
        _n_nonce++;
        _s_hash = _calculateHash();
    } while(_s_hash.substr(0, n_difficulty) != str);
    std::cout << "DONE" << std::endl;
}

// use the SHA256 algorithm to calculate hash
inline std::string block::_calculateHash() const {
    // stringstreams are useful for interfacing various types with strings - works like iostream
    std::stringstream ss;
    ss << _n_index << _t_time << _s_data << _n_nonce << s_prev_hash;

    return sha256(ss.str());;
}