# Deepfake Detection

#### April 20th, 2022
- created a new branch for `comms` - it's taking longer than expected but is still very important
- made the decision to use `Boost::Asio` as a networking library to make comms simpler

#### April 13th, 2022
- TV interview

#### March 16th, 2022
- nodes now have a map from the IDs of all other nodes to their contact information

#### March 15th, 2022
- each node can now create its own socket on a unique port
- function to close socket
- first test case - create a socket

#### March 14th, 2022
- TCP socket initialization, each node creates a socket

#### March 6th, 2022
- global node list part 2 (finished), all nodes can read from the folder

#### March 2nd, 2022
- global node list part 1, all nodes publish a file to a folder

#### March 1st, 2022
- modified `interactivesystemtest.cpp` to include searching the chain
- updated the Makefile to build multiple targets
- we can now run nodes as their own programs
- added a simulation which creates many node processes

Finished with v0.1! Beginning work on v0.2.

#### February 22nd, 2022
- perceptual image hashing finished, needs debugging
- removed `main.cpp`, `tests/interactive_system_test.cpp` is now used as file for testing
- integrated image hashing with other functions
- updated Makefile
- refactored code
- restructured files and folders
- added `doge.jpeg`, `mars.jpeg`, and `color.jpeg` for testing
- added `num_blocks` field for blockchain object
- adjusted CLI output

Almost completed v0.1! Light debugging of hashing necessary before done.

#### February 21st, 2022
- finished the first version of perceptual image hashing (rough)

#### February 14th, 2022
- added pseudocode framework for image hashing, still needs to be implemented
- chose an image I/O library

#### February 9th, 2022
- added a framework for a full system test, can't actually test anything until image hashing is ready

#### February 8th, 2022
- added a global list of nodes so nodes are aware of all others
- installed lightweight unit testing framework (open source on Github)

#### February 7th, 2022
- removed `using namespace std` from all files, added `std::` prefixes
- `main.cpp` can now handle variable numbers of blocks, each with their own unique string data
- created `blockchain::display(void)` function to output the blockchain (visually) to CLI
- added more/cleaned comments
- adjusted CLI output

Made client more user-friendly.

#### February 6th, 2022
- created `blockchain.h` and `blockchain.cpp` for data structure
- created `block.h` and `block.cpp` for block objects
- `main.cpp` creates 1 genesis block and 3 extra blocks for testing purposes
- created dummy `node` class
- created `comm` files 
- created Makefile for outputting `a.out`, with `make clean` command to delete `a.out`

Project currently uses SHA-256 algorithm for hashing during block mining (found online: http://www.zedwood.com/article/cpp-sha256-function). Current TestChain is proof-of-work (PoW), not sure how to make it proof-of-stake (PoS), or if even necessary. Current TestChain is only able to handle strings as block data, will need to upgrade this to other forms of media (specifically videos). "Nodes" will eventually be the primary actors in the network, acting as individual computers on the network. Comm library will abstract away all communication details. Need to change namespace as this can cause problems for larger projects - basically delete `using namespace std`.
