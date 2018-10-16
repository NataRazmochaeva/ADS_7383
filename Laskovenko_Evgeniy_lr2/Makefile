all: main.o functions.o atoms.o pair.o list.o
	g++ main.o functions.o atoms.o pair.o list.o -o start

main.o: main.cpp header.h atoms.h pair.h list.h
	g++ -c main.cpp
functions.o: functions.cpp header.h atoms.h pair.h list.h
	g++ -c functions.cpp
atoms.o: atoms.cpp atoms.h
	g++ -c atoms.cpp
pair.o: pair.cpp pair.h list.h
	g++ -c pair.cpp
list.o: list.cpp list.h pair.h
	g++ -c list.cpp

clean:
	rm *.o start 