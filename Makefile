### Makefile --- 

## Author: IkJung Yun
## Date: 2012.01.10

# .SUFFIXES = .cpp .o

OBJECTS = 

CC = g++

TARGET = node_test elem_test

CFLAGS = -g -Wall #-D_ELEM_DEBUG_NON_SINGULAR_

all : node elem_test

###########################
# Elem related definition #
###########################

## Test test for elem
elem_test : elem.o elem_test.o
	$(CC) -o elem_test elem.o elem_test.o

elem_test.o : elem_test.cpp elem.h elem.cpp
	$(CC) $(CFLAGS) -c elem_test.cpp

## Elem defined header file and class
elem.o : elem.h elem.cpp Numerical_Integration.h common.h
	$(CC) $(CFLAGS) -c elem.cpp

###########################
# Node related definition #
###########################

node_test : node.o node_test.o common.h
	$(CC) -o node_test node.o node_test.o

node_test.o : node_test.cpp node.h node.cpp
	$(CC) $(CFLAGS) -c node_test.cpp

## Node defined header file and class
node.o : node.h node.cpp
	$(CC) $(CFLAGS) -c node.cpp

clean :
	rm $(TARGET) *.o


### Makefile ends here



