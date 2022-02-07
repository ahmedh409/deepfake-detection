// comm.cpp
#include "comm.h"

#include <iostream>
#include <string>

void send(std::string message) {
    std::cout << "Sending message: " << message << std::endl;
}

void recv() {
    std::cout << "Receiving message" << std::endl;
}