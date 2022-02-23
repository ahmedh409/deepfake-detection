// an interactive full system test

// FILE INCLUDES
#include "./../blockchain/blockchain.h"
#include "./../hashing/phash.h"
#include "./../simulation/node.h"
#include "./../hashing/phash.h"
// LIBRARY INCLUDES
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
// MACRO DEFINITIONS
#define n_difficulty    2

// GLOBAL VARIABLES
blockchain test_chain = blockchain(n_difficulty); // create blockchain with hash difficulty as parameter


std::string output_hash(void) {
    std::cout << "Enter an image path" << std::endl;
    std::cout << "> ";

    std::string file_path;
    std::cin >> file_path;
    std::cout << "File path: " << file_path << std::endl;
    std::string hash = generate_phash(file_path);
    std::cout << "Image hash: " << hash << std::endl;

    return file_path;
}

bool add_hash_to_chain(void) {
    std::cout << "Enter an image path" << std::endl;
    std::cout << "> ";

    std::string file_path;
    std::cin >> file_path;
    std::cout << "Hashing image..." << std::endl;
    test_chain.addBlock(block(test_chain.num_block, generate_phash(file_path)));

    return true;
}

bool search_chain(void) {
    std::cout << "Not implemented." << std::endl;
    return true;
}

bool display_chain(void) {
    test_chain.display();
    return true;
}


int main() {
    int selection = 0;
    while (selection != 5) {
        std::cout << std::endl;
        std::cout << "--------------------------------" << std::endl;
        std::cout << "\tOPTIONS" << std::endl;
        std::cout << "--------------------------------" << std::endl;
        std::cout << "1: Output hash for image" << std::endl;
        std::cout << "2: Add image to chain" << std::endl;
        std::cout << "3: Search the chain for an image" << std::endl;
        std::cout << "4: Display information" << std::endl;
        std::cout << "5: Quit" << std::endl;
        std::cout << "--------------------------------" << std::endl;
        std::cout << "> ";

        std::cin >> selection;
        if (std::cin.fail()) {
            std::cout << "**Invalid input**" << std::endl;
            std::cin.clear();
            std::cin.ignore();
            sleep(1);
            continue;
        } 

        switch (selection) {
            case 1:
                output_hash();
                sleep(1);
                break;
            case 2:
                add_hash_to_chain();
                sleep(1);
                break;
            case 3:
                search_chain();
                sleep(1);
                break;
            case 4:
                display_chain();
                sleep(1);
                break;
            case 5:
                break;
        }
    }
}