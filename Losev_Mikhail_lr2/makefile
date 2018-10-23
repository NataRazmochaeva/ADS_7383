all: l_mod1.o l_impl.o
	g++ l_mod1.o l_impl.o -o l_mod1
l-mod1.o: l_mod1.cpp l_intrfc.h
	g++ -c l_mod1.cpp
l_impl.o:l_impl.cpp
	g++ -c l_impl.cpp
clean:
	rm *.o l_mod1 result.png