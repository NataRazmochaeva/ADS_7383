CXX=g++
RM=rm -f
LDFLAGS=-g -Wall

SRCS=main.cpp action.cpp binkor.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS)

main.o: main.cpp main.h

action.o: action.cpp action.h

binkor.o: binkor.cpp binkor.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) main