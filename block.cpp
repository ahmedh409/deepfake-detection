#include <sstream>
#include "block.h"
#include "sha256.h"

block::block(uint32_t n_index_in, const string &s_data_in) : _n_index(n_index_in), _s_data(s_data_in) {
    _n_nonce = -1;
    _t_time = time(nullptr);
}

string block::getHash() {
    return _s_hash;
}

void block::mineBlock(uint32_t n_difficulty) {
    // create string array with 1 more value than spec'd in n_difficulty
    char cstr[n_difficulty + 1];
    
    // fill array with zeroes, add string terminator character
    cout << "\t...filling hash array with zeroes and performing conversions...";
    for (uint32_t i = 0; i < n_difficulty; ++i) cstr[i] = '0';
    cstr[n_difficulty] = '\0';
    string str(cstr); // convert to standard string 
    cout << "DONE\n\t...calculating SHA-256 hash...";

    // do-whiles run at least once (exit control loop)
    do {
        _n_nonce++;
        _s_hash = _calculateHash();
    } while(_s_hash.substr(0, n_difficulty) != str);
    cout << "DONE" << endl;
}

// use the SHA256 algorithm to calculate hash
inline string block::_calculateHash() const {
    stringstream ss;
    ss << _n_index << _t_time << _s_data << _n_nonce << s_prev_hash;

    return sha256(ss.str());;
}