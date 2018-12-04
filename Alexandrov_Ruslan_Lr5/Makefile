CXX=g++
RM=rm -f
LDFLAGS=-g -Wall

SRCS=main.cpp codetree.cpp fs.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS)

main.o: main.cpp main.h

codetree.o: codetree.cpp codetree.h

fs.o: fs.cpp fs.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) main