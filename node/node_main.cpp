#include "node.h"
#include <stdlib.h>

int main (int argc, char** argv) {
    if (argc != 2) {
        return -1;
    }
    int id = atoi(argv[1]);
    
    Node n(id);
}