# using -Og compiler optimization to make debugging easier
# include the root directory when searching for files
COMPILER_FLAGS = -Og -I ./

CORE_FILES = blockchain/block.o blockchain/blockchain.o blockchain/sha256.o \
			hashing/phash.o \
			node/comm.o node/node.o

all : node tests/interactive_system_test.o
	g++ $(COMPILER_FLAGS) -o a.out $(CORE_FILES) \
		tests/interactive_system_test.o

sim : node tests/simulation.o
	g++ $(COMPILER_FLAGS) -o sim.out $(CORE_FILES) \
		tests/simulation.o

node : 	$(CORE_FILES) node/node_main.o
	g++ $(COMPILER_FLAGS) -o node.out $(CORE_FILES) node/node_main.o

run :	
	./a.out

clean :
	rm -r -f *a.out temp/*
	find . -type f -name '*.o' -delete
