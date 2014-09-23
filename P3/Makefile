# A simple makefile for CSE 100 P3

CC=g++
CXXFLAGS=-g
LDFLAGS=-g

all: compress uncompress

compress: BitInputStream.o BitOutputStream.o HCNode.o HCTree.o

uncompress: BitInputStream.o BitOutputStream.o HCNode.o HCTree.o

HCTree.o: BitInputStream.hpp BitOutputStream.hpp HCNode.hpp HCTree.hpp

HCNode.o: HCNode.hpp

BitOutputStream.o: BitOutputStream.hpp

BitInputStream.o: BitInputStream.hpp

clean:
	rm -f compress uncompress *.o core*

purify:
	prep purify
	purify -cache-dir=$HOME g++ compress.cpp BitOutputStream.cpp BitInputStream.cpp HCTree.cpp HCNode.cpp -o compress

	purify -cache-dir=$HOME g++ uncompress.cpp BitOutputStream.cpp BitInputStream.cpp HCTree.cpp HCNode.cpp -o uncompress
