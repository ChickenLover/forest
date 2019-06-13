CC=g++ --std=c++17

all: bin_tree.o interface.o
	$(CC) -o tree bin_tree.o interface.o

bin_tree.o: bin_tree.cpp
	$(CC) -c bin_tree.cpp

interface.o: interface.cpp
	$(CC) -c interface.cpp

clear:
	rm -f tree bin_tree.o interface.o
