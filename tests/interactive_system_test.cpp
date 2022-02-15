// an interactive full system test

#include <iostream>
#include <string>
#include <unistd.h>
#


std::string generate_hash() {
    std::cout << "Enter an image path" << std::endl;
    std::cout << "> ";

    std::string file_path;
    std::cin >> file_path;
    std::cout << "File path: " << file_path << std::endl;

    return file_path;
}

bool add_hash_to_chain(std::string hash) {
    std::cout << "Adding hash to chain" << std::endl;
    return true;
}

bool search_chain(std::string hash) {
    std::cout << "Searching for hash in chain" << std::endl;
    return true;
}

bool display_chain() {
    std::cout << std::endl;
    return true;
}


int main() {
    int selection = 0;
    while (selection != 4) {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Options" << std::endl;
        std::cout << "--------------------------------" << std::endl;
        std::cout << "1: Generate hash for image" << std::endl;
        std::cout << "2: Add image hash to chain" << std::endl;
        std::cout << "3: Search the chain for an image" << std::endl;
        std::cout << "4: Display current chain" << std::endl;
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
                generate_hash();
                sleep(1);
                break;
            case 2:
                add_hash_to_chain(generate_hash());
                sleep(1);
                break;
            case 3:
                search_chain(generate_hash());
                sleep(1);
                break;
            case 4:

                sleep(1);
                break;
            case 5:
                break;
        }
    }
}