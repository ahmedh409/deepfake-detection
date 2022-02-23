# we don't need to use compiler optimizations yet
# they make it harder to debug and test things
# only needed once we start working on production code
all :
	g++ -o a.out ./tests/interactive_system_test.cpp ./blockchain/block.cpp ./blockchain/blockchain.cpp ./blockchain/sha256.cpp ./simulation/node.cpp ./simulation/comm.cpp ./hashing/phash.cpp -fsanitize=address -fno-omit-frame-pointer -g

run :	
	./a.out

clean :
	rm ./a.out temp/*
