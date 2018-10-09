all: run
	
run: main.o func.o func.hpp
	g++ main.o func.o -o run
main.o: main.cpp func.hpp
	g++ -c  main.cpp
func.o: func.cpp func.hpp
	g++ -c func.cpp 
clean: rm -rf *.o
