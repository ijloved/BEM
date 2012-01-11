### Makefile --- 

## Author: IkJung Yun
## Date: 2012.01.10

# .SUFFIXES = .cpp .o

OBJECTS = node.o

CC = g++

TARGET = node_test

CFLAGS = -g -Wall

all : node


###########################
# Node related definition #
###########################

## Test test for node
node_test : node.o node_test.o
	$(CC) -o node_test node.o node_test.o

node_test.o : node_test.cpp node.h node.cpp
	$(CC) $(CFLAGS) -c node_test.cpp

## Node defined header file and class
node.o : node.h node.cpp
	$(CC) $(CFLAGS) -c node.cpp

clean :
	rm $(TARGET) *.o


### Makefile ends here



