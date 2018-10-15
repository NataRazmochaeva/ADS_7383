all: main.o fun.o
	gcc main.o fun.o -o lr2

main.o: main.c fun.c
	gcc -c main.c

fun.o: fun.c fun.h
	gcc -c fun.c

clean:
	rm *.o lr2
