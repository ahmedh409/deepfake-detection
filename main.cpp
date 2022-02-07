#include "blockchain.h"
#include <iostream>
#include <string>
#include <vector>

// Tutorial used: https://davenash.com/2017/10/build-a-blockchain-with-c/n

int main() {
    blockchain test_chain = blockchain(4); // create blockchain with hash difficulty as parameter

    std::cout << "\nCryptographic algorithm used: SHA-256" << std::endl;
    std::cout << "n_difficulty is set to " << test_chain.display_diff << "; higher numbers take longer to hash" << std::endl;
    std::cout << "Most of this is from a tutorial online, link commented in main.cpp\n" << std::endl;

    std::cout << "How many blocks would you like to add to the TestChain? ";
    int num_blocks; std::cin >> num_blocks;
    std::string data[num_blocks];
    for (int i = 0; i < num_blocks; i++) {
        std::cout << "   Enter data contained in block " << i+1 << ": ";
        std::cin >> data[i];
    }

    std::cout << "\n===== TESTCHAIN =====" << std::endl;

    for (int i = 0; i < num_blocks; i++) {
        std::cout << "MINING BLOCK " << i+1 << " -> ";
        test_chain.addBlock(block(i+1, data[i]));
    }

    std::cout << std::endl;

    test_chain.display();

    std::cout << std::endl;

    return 0;
}