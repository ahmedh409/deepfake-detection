# Deepfake Detection

#### February 7th, 2022
- removed `using namespace std` from all files, added `std::` prefixes
- `main.cpp` can now handle variable numbers of blocks, each with their own unique string data
- created `blockchain::display(void)` function to output the blockchain (visually) to CLI
- added more/cleaned comments
- adjusted CLI output
Made client more user-friendly.

##### February 6th, 2022
- created `blockchain.h` and `blockchain.cpp` for data structure
- created `block.h` and `block.cpp` for block objects
- `main.cpp` creates 1 genesis block and 3 extra blocks for testing purposes
- created dummy `node` class
- created `comm` files 
- created Makefile for outputting `a.out`, with `make clean` command to delete `a.out`

Project currently uses SHA-256 algorithm for hashing during block mining (found online: http://www.zedwood.com/article/cpp-sha256-function). Current TestChain is proof-of-work (PoW), not sure how to make it proof-of-stake (PoS), or if even necessary. Current TestChain is only able to handle strings as block data, will need to upgrade this to other forms of media (specifically videos). "Nodes" will eventually be the primary actors in the network, acting as individual computers on the network. Comm library will abstract away all communication details. Need to change namespace as this can cause problems for larger projects - basically delete `using namespace std`.
