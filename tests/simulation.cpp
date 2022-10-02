#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "simulator.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Invalid arguments" << std::endl;
        return -1;
    }

    int num_nodes = atoi(argv[1]);

    Simulator s(num_nodes);
    std::cout << "HEY WTF" << std::endl;
    s.send_command(0, "add /home/sam/research/deepfake/code/color.jpeg");
    s.terminate_after(12);
    return 0;
}