#include <iostream>
#include <cstdint>
#include <string>

using namespace std;

class block {
public:
    string s_prev_hash;

    // pass-by-reference/pointer is faster than pass-by-value if (size of value) > (size of pointer) --- used for s_data_in
    block(uint32_t n_index_in, const string &s_data_in);

    string getHash();

    void mineBlock(uint32_t n_difficulty);

private:
    uint32_t _n_index;
    int64_t _n_nonce;
    string _s_data;
    string _s_hash;
    time_t _t_time;

    string _calculateHash() const;
};