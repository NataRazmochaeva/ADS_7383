CXX=g++
RM=rm -f
LDFLAGS=-g -Wall

SRCS=main.cpp binom.cpp helper.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS)

main.o: main.cpp main.h

binom.o: binom.cpp binom.h

helper.o: helper.cpp helper.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) main