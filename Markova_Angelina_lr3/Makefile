all: main.o fun.o
	g++ main.o fun.o -o lr2
main.o: main.cpp fun.cpp
	g++ -c main.cpp
fun.o: fun.cpp fun.h
	g++ -c fun.cpp
clean:
	rm *.o lr2
