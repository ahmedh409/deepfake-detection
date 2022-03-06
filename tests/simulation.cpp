#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Invalid arguments" << std::endl;
        return -1;
    }

    int num_nodes = atoi(argv[1]);

    for (int i = 0; i < num_nodes; i++) {
        // create new process, check if it is the child process
        if (fork() == 0) {
            char program[] = "./node.out";
            const char* id = std::to_string(i + 1).c_str();
            char id_final[10];
            strcpy(id_final, id);
            char* argv[] = {program, id_final, NULL};
            execv(program, argv);
            exit(0);
        }
        usleep(100000);
    }

    for (int i = 0; i < num_nodes; i++) {
        // wait for all children
        int status;
        wait(&status);
    }
}