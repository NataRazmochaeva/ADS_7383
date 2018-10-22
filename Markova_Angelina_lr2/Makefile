all: main.o list.o
	g++ main.o list.o -o lr2

main.o: main.cpp list.cpp
	g++ -c main.cpp

list.o: list.cpp list.h
	g++ -c list.cpp

clean:
	rm *.o lr2
