all: main.o bin_rocker.o
	g++ main.o bin_rocker.o -o bin_rocker
main.o: main.cpp bin_rocker.hpp
	g++ main.cpp -std=c++14 -c
bin_rocker.o: bin_rocker.cpp bin_rocker.hpp
	g++ bin_rocker.cpp -std=c++14 -c
