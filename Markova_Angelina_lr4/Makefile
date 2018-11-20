all: lab_rab4

lab_rab4: main.o fun.o
	g++ main.o fun.o -o lr4

lab4.o: main.cpp
	g++ -c main.cpp

fun.o: fun.cpp
	g++ -c fun.cpp

clean:
	rm -rf *.o lr4
