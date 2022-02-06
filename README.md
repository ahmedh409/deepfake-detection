# Deepfake Detection

--- February 6th, 2022
- added block.h/.cpp and blockchain.h/.cpp
- uses SHA-256 for hashing during block mining (found online: http://www.zedwood.com/article/cpp-sha256-function)
- proof-of-work (PoW), not sure how to make it proof-of-stake (PoS)
- currently only able to handle strings as data; will need to upgrade this to other forms of media (specifically videos)
- created `blockchain.h` and `blockchain.cpp` for data structure
- created `block.h` and `block.cpp` for block objects
- makefile for creating `a.out` 
- uses SHA-256 algorithm for hashing during block mining (found online: http://www.zedwood.com/article/cpp-sha256-function)
- current blockchain is proof-of-work (PoW), not sure how to make it proof-of-stake (PoS)
- only able to handle strings as data; will need to upgrade this to other forms of media (specifically videos)
- main.cpp creates 1 genesis block and 3 extra blocks for testing purposes