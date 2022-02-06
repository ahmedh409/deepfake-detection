#include "blockchain.h"
#include <iostream>

// Tutorial used: https://davenash.com/2017/10/build-a-blockchain-with-c/n

using namespace std;

int main() {
    blockchain test_chain = blockchain();

    cout << "Cryptographic algorithm used: SHA-256" << endl;
    cout << "\nn_difficulty is set to 3; higher numbers take longer to hash" << endl;
    cout << "Most of this is from a tutorial online, link commented in main.cpp\n" << endl;

    cout << "Mining block 1..." << endl;
    test_chain.addBlock(block(1, "Block 1 Data"));

    cout << "Mining block 2..." << endl;
    test_chain.addBlock(block(2, "Block 2 Data"));

    cout << "Mining block 3..." << endl;
    test_chain.addBlock(block(3, "Block 3 Data"));

    cout << endl;

    return 0;
}