CC=g++ --std=c++17

all: tree.o
	$(CC) -o tree tree.o

tree.o: tree.cpp
	$(CC) -c tree.cpp

clear:
	rm -f tree tree.o
