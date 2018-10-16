CC = g++
OBJ = main.o

all: hello
	
hello: $(OBJ)
	$(CC) $(OBJ) -o lr2
$(OBJ): %.o: %.cpp
	$(CC) -c $< -o $@ 
clean:
	rm *.o
	rm lr2
