# A simple makefile for CSE 100 P2

#use g++ for everything
CC= g++  	

# include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -std=c++11 -g -Wall

#include debugging symbols in executable
LDFLAGS= -g	

bench: benchtree.o
	g++ -o bench benchtree.o countint.o

rst: test_RST.o
	g++ -o rst test_RST.o countint.o

bst: test_BST.o 
	g++ -o bst test_BST.o
benchtree.o: BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp countint.o
test_RST.o: BST.hpp BSTNode.hpp BSTIterator.hpp RST.hpp countint.o
test_BST.o: BST.hpp BSTNode.hpp BSTIterator.hpp 

countint.o: countint.hpp
clean: 
	rm bst rst bench *.o

