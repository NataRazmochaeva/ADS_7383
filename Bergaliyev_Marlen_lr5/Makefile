all: main.o CodeTree.o
	g++ main.o CodeTree.o -o ShannonFano
main.o: main.cpp CodeTree.hpp
	g++ main.cpp -std=c++14 -c
CodeTree.o: CodeTree.cpp CodeTree.hpp
	g++ CodeTree.cpp -std=c++14 -c
