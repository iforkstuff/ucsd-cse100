# A simple makefile for CSE 100 P4

CC=g++
CXXFLAGS=-g
LDFLAGS=-g

all: netplan

netplan: graph.o vertex.o edge.o 

graph.o: graph.hpp vertex.hpp edge.hpp 

vertex.o: vertex.hpp

edge.o: edge.hpp

clean:
	rm -f netplan *.o core*

purify:
	prep purify
	purify -cache-dir=$HOME g++ netplan.cpp graph.cpp vertex.cpp edge.cpp -o netplan
