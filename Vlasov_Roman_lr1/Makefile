CC = g++
OBJ = main.o permutations.o

all: hello
	
hello: $(OBJ)
	$(CC) $(OBJ) -o lr1
$(OBJ): %.o: %.cpp permutations.h
	$(CC) -c $< -o $@ 
clean:
	rm *.o
	rm lr1
