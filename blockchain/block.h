#include <iostream>
#include <cstdint>
#include <string>

class block {
public:
    std::string s_prev_hash;

    // pass-by-reference/pointer is faster than pass-by-value if (size of value) > (size of pointer) --- used for s_data_in
    block(uint32_t n_index_in, const std::string &s_data_in);

    std::string getHash();

    void mineBlock(uint32_t n_difficulty);

    std::string data;

    uint32_t n_index;

private:
    int64_t _n_nonce;
    std::string _s_data;
    std::string _s_hash;
    time_t _t_time;

    std::string _calculateHash() const;
};