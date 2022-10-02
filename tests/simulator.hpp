#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

class Simulator {

public:

    Simulator(int num_nodes) : num_nodes(num_nodes) {
        this->launch_nodes();
        sleep(4);
    }

    // sleep then shutdown the nodes
    void terminate_after(int seconds) {
        sleep(seconds);
        this->shutdown_nodes();
    }

    int num_nodes;
    std::vector<int> pipes;

    // launch node processes
    void launch_nodes() {
        for (int i = 0; i < this->num_nodes; i++) {
            // create the command to pass to execv
            char program[] = "./node.out";
            const char* id = std::to_string(i).c_str();
            char id_final[10];
            strcpy(id_final, id);
            char* argv[] = {program, id_final, NULL};

            // create the pipe and check for error
            int pipefd[2];
            if (pipe(pipefd) < 0) {
                printf("Error creating pipe\n");
                return;
            }

            // create the new process and attach its standard input to the pipe
            int f = fork();
            if (f < 0) {
                // error
                printf("Error forking process\n");
                return;
            } else if (f == 0) {
                // child
                close(pipefd[1]);   // close output pipe
                dup2(pipefd[0], STDIN_FILENO);  // redirect pipe input to standard input
                close(pipefd[0]);

                execv(program, argv);
                exit(0);
            } else {
                // parent
                close(pipefd[0]);
                this->pipes.push_back(pipefd[1]);
            }
        }
    }

    // at the end of the simulation, shutdown the nodes
    void shutdown_nodes() {
        for (int i = 0; i < this->num_nodes; i++) {
            close(this->pipes[i]);
            int status;
            wait(&status);
        }
    }

    // pass a command to the node's standard input
    // this function checks if the node ID is valid so the public functions don't have to
    void send_command(int node_id, std::string command) {
        if ((node_id < 0) || (node_id >= this->num_nodes)) {
            printf("Invalid node ID\n");
            return;
        }

        // write to the file and add space after to ensure the last word is read
        command += "\n";
        write(this->pipes[node_id], command.c_str(), command.size());
    }

};

#endif