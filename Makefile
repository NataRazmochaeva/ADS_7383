all: main.o bt_func.o func.o
	g++ main.o  bt_func.o func.o -o tree
work_bt.o: main.cpp Btree.h func.h
	g++ -c main.cpp
functions.o: func.cpp func.h Btree.h
	g++ -c func.cpp
bt_implementation.o: bt_func.cpp Btree.h
	g++ -c bt_func.cpp
clean:
	rm *.o bt_func 
