CC=g++ --std=c++17
OPT=-c -fPIC

all: bin_tree.o interface.o
	$(CC) -o tree bin_tree.o interface.o

lib: bin_tree.o
	$(CC) bin_tree.o -o libtree.so -shared

bin_tree.o: bin_tree.cpp
	$(CC) $(OPT) bin_tree.cpp

interface.o: interface.cpp
	$(CC) $(OPT) interface.cpp

clear:
	rm -f tree bin_tree.o interface.o
