all: main.o relatives.o
	g++ main.o relatives.o -o relatives
main.o: main.cpp relatives.hpp
	g++ -c -std=c++14 main.cpp
relatives.o: relatives.cpp relatives.hpp
	g++ -c -std=c++14 relatives.cpp
