#Jonathan Pham
#CS4280 P3
#04/29/19

CC = gcc
CFLAGS = -g -Wall
TARGET = statSem
OBJ = P3.o scanner.o parser.o testTree.o identifierStack.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

P3.o: P3.c node.h parser.h testTree.h
scanner.o: scanner.c character.h token.h testTree.h scanner.h
parser.o: parser.c token.h node.h scanner.h testTree.h parser.h
testTree.o: testTree.c token.h node.h identifierStack.h testTree.h
identifierStack.o: identifierStack.c identifierStack.h

clean:
	rm -f $(TARGET) $(OBJ)


