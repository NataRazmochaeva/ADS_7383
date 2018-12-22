CXX=g++
RM=rm -f
LDFLAGS=-g -Wall

SRCS=main.cpp codetree.cpp fs.cpp helper.cpp huffman.cpp priority_queue.h
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS)

main.o: main.cpp main.h

codetree.o: codetree.cpp codetree.h

helper.o: helper.cpp helper.h

fs.o: fs.cpp fs.h

huffman.o: huffman.cpp huffman.h

priority_queue.h.o: priority_queue.h.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) main