CC = g++
OBJ = lr2.o list.o
	
all: $(OBJ)
	$(CC) $(OBJ) -o lr2
$(OBJ): %.o: %.cpp list.h
	$(CC) -c $< -o $@ 
clean:
	rm *.o
	rm lr2
