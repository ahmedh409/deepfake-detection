# we don't need to use compiler optimizations yet
# they make it harder to debug and test things
# only needed once we start working on production code
all :
	g++ -o a.out main.cpp block.cpp blockchain.cpp sha256.cpp node.cpp comm.cpp phash.cpp -fsanitize=address -fno-omit-frame-pointer -g

run :	
	./a.out

clean :
	rm ./a.out temp/*
