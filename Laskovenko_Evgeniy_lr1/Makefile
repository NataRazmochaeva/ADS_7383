all: main.o function.o
	g++ main.o function.o -o start

main.o: main.cpp function.hpp
	g++ main.cpp
function.o: function.cpp
	g++ function.cpp

clean:
	rm *.o start 
