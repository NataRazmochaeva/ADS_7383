all: work_bt.o bt_implementation.o functions.o
	g++ work_bt.o  bt_implementation.o functions.o -o work_bt

work_bt.o: work_bt.cpp Btree.h functions.h
	g++ -c work_bt.cpp
functions.o: functions.cpp functions.h Btree.h
	g++ -c functions.cpp

bt_implementation.o: bt_implementation.cpp Btree.h
	g++ -c bt_implementation.cpp
clean:
	rm *.o bt_implementation 