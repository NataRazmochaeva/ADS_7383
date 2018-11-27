CXX=g++
RM=rm -f
LDFLAGS=-g -Wall

SRCS=main.cpp actions.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS)

main.o: main.cpp main.h

actions.o: actions.cpp actions.h

btree.o: btree.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) main