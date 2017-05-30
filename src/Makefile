
OBJS = suffixTree.o edge.o node.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++11 $(DEBUG)
LFLAGS = -Wall $(DEBUG)
EXEC = suffixTree
all: $(OBJS)
			$(CC) $(LFLAGS) $(OBJS) -o $(EXEC)

main.o : main.cpp suffixTree.h
			$(CC) $(CFLAGS) main.cpp

node.o : node.h node.cpp
			$(CC) $(CFLAGS) node.cpp

edge.o : edge.h edge.cpp node.h
	    $(CC) $(CFLAGS) edge.cpp

suffixTree.o : suffixTree.h suffixTree.cpp node.h edge.h
	    $(CC) $(CFLAGS) suffixTree.cpp
clean:
	rm -f $(OBJS)
	rm -f $(EXEC)
run:
	./$(EXEC)
