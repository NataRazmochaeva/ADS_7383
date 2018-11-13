CXX=g++
RM=rm -f
LDFLAGS=-g -Wall

SRCS=main.cpp binkor.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS)

main.o: main.cpp main.h

binom.o: binkor.cpp binkor.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) main