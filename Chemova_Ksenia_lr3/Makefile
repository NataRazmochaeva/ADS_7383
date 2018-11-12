all: main.o stack.o
	g++ main.o stack.o -o lab3
main.o: main.cpp stack.cpp
	g++ -c main.cpp
stack.o: stack.cpp stack.hpp
	g++ -c stack.cpp
clean:
	rm *.o lr3
