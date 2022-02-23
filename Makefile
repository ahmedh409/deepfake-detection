# using -Og compiler optimization to make debugging easier
all :
	g++ -o a.out -Og ./tests/interactive_system_test.cpp ./blockchain/block.cpp ./blockchain/blockchain.cpp ./blockchain/sha256.cpp ./simulation/node.cpp ./simulation/comm.cpp ./hashing/phash.cpp -fsanitize=address -fno-omit-frame-pointer -g

run :	
	./a.out

clean :
	rm ./a.out temp/*
