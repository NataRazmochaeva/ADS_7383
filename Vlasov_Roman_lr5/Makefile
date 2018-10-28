CC = g++
OBJ = main.o

all: hello
	
hello: $(OBJ)
	$(CC) $(OBJ) -o lr5
$(OBJ): %.o: %.cpp
	$(CC) -c $< -o $@ 
clean:
	rm *.o
	rm lr5
