all: main.o functions.o
	g++ main.o functions.o -o main
main.o: main.cpp bst_interf.h functions.h
	g++ -c main.cpp
functions.o: functions.cpp bst_interf.h functions.h
	g++ -c functions.cpp


