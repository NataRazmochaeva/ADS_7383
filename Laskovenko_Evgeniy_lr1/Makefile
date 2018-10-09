all: main.o function.o
	g++ main.o function.o -o start

main.o: main.cpp function.hpp
	g++ -c main.cpp
function.o: function.cpp function.hpp
	g++ -c function.cpp

clean:
	rm *.o start 
